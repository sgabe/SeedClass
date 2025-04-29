# -*- coding: utf-8 -*-
#!/usr/bin/env python

"""
SeedSort is a Python script to analyze crash samples with BugID and sort them in a multi-threaded manner.

Example:
    python SeedSort.py -i ./input_folder -o ./output_folder -t 8
"""

__author__    = 'Gabor Seljan'
__version__   = '0.8.5'
__date__      = '2025/04/24'
__copyright__ = 'Copyright (c) 2025 Gabor Seljan'
__license__   = 'MIT'

import os
import re
import sys
import shutil
import signal
import logging
import argparse
import subprocess
import threading
import concurrent.futures

stop = threading.Event()

logging.basicConfig(
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S',
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('SeedSort.log', mode='w'),
        logging.StreamHandler()
    ]
)

print('''
                   _____               _  _____            _
                  / ____|    v{}   | |/ ____|          | |
                 | (___   ___  ___  __| | (___   ___  _ __| |_
                  \\___ \\ / _ \\/ _ \\/ _` |\\___ \\ / _ \\| '__| __|
                  ____) |  __/  __/ (_| |____) | (_) | |  | |_
                 |_____/ \\___|\\___|\\__,_|_____/ \\___/|_|   \\__|

'''.format(__version__))


def handle_exit_signal(signum, frame):
    if not stop.is_set():
        logging.warning('Interrupt received, exiting gracefully...')
        stop.set()


def run_bugid(file, files, crash_dir, clean_dir, lock):
    '''Executes BugId on the given file, checks stdout for bugs, and moves crashing/non-crashing files immediately.'''
    if stop.is_set():
        return

    cmd = [
        'C:\\Tools\\BugID\\BugId.cmd',
        '-q',
        '--collateral=1',
        '--bShowLicenseAndDonationInfo=false',
        '--bGenerateReportHTML=false',
        '--cBugId.bEnsurePageHeap=false',
        '--isa=x86',
        'C:\\Tools\\Harness\\GDI.exe',
        '--',
        '-f',
        file
    ]

    size = os.path.getsize(file)

    proc = subprocess.run(cmd, capture_output=True, text=True, encoding='utf-8', errors='replace')
    stdout = proc.stdout if proc.stdout else ""

    logging.debug(f'BugId output:\n{stdout}')

    if 'A bug was detected' in stdout:
        match = re.search(r"Id @ Location:\s+\S+\s+(\w+\.\w+) @ [^!]+!(\w+\.\w+)!(.+)", stdout)
        if match:
            bugid, library, function = match.groups()
            logging.info(f'File {os.path.basename(file)} with {size} bytes triggered bug {bugid} in {function} within {library}.')

            crashes = os.path.join(crash_dir, os.path.basename(file))
            shutil.move(file, crashes)

            with lock:
                if bugid not in files or size < files[bugid][1]:
                    files[bugid] = (crashes, size, function, library)
        else:
            logging.error(f'File {os.path.basename(file)} with {size} bytes triggered a bug but failed to extract identifier information!')
    elif not stop.is_set():
        shutil.move(file, os.path.join(clean_dir, os.path.basename(file)))
        logging.warning(f'File {os.path.basename(file)} with {size} bytes did not trigger a bug.')


def process_files(input_dir, crash_dir, clean_dir, max_threads):
    '''Processes each file in the directory concurrently and tracks the smallest file per unique identifier.'''

    file_count = len([f for f in os.listdir(input_dir) if os.path.isfile(os.path.join(input_dir, f))])
    logging.info(f'Found {file_count} files in input directory {input_dir}.')

    files = {}
    lock = threading.Lock()

    def process_file(filename):
        if stop.is_set():
            return

        file = os.path.join(input_dir, filename)
        if not os.path.isfile(file):
            logging.debug(f'Skipping non-file {file}.')
            return
        run_bugid(file, files, crash_dir, clean_dir, lock)

    try:
        with concurrent.futures.ThreadPoolExecutor(max_workers=max_threads) as executor:
            futures = [executor.submit(process_file, filename) for filename in os.listdir(input_dir)]
            for future in concurrent.futures.as_completed(futures):
                if stop.is_set():
                    for future in futures:
                        future.cancel()
                    executor.shutdown(wait=False)
                    break
    except Exception as e:
        logging.error(f'Exception occurred during processing: {e}')

    if not files:
        logging.warning('No unique bugs detected!')

    return files


def copy_unique_files(files, unique_dir):
    '''Copies the smallest file for each unique identifier to the UNIQUE directory.'''
    for bugid, (file, size, function, library) in files.items():
        dst = os.path.join(unique_dir, os.path.basename(file))
        shutil.copy(file, dst)
        logging.info(f'Copied smallest file {os.path.basename(file)} with {size} bytes triggering bug {bugid} in {function} within {library}.')


def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description='Process files with BugID, track crashes, and store unique bug samples.',
        prog='SeedSort'
    )

    parser.add_argument('-i', '--input', required=True,
                        help='input folder containing files to process')
    parser.add_argument('-o', '--output', required=True,
                        help='output folder where other folders will be created')
    parser.add_argument('-t', '--threads', type=int, default=None,
                        help='maximum number of threads for processing')

    args = parser.parse_args()

    if not os.path.exists(args.input) or not os.path.isdir(args.input):
        logging.error(f'Input folder {args.input} does not exist or is not a directory!')
        sys.exit(1)

    crash_dir = os.path.join(args.output, 'CRASH.all')
    unique_dir = os.path.join(args.output, 'CRASH.unique')
    clean_dir = os.path.join(args.output, 'CRASH.none')

    os.makedirs(crash_dir, exist_ok=True)
    os.makedirs(unique_dir, exist_ok=True)
    os.makedirs(clean_dir, exist_ok=True)

    signal.signal(signal.SIGINT, handle_exit_signal)

    max_threads = args.threads if args.threads else min(32, os.cpu_count() + 4)
    logging.info(f'Using {max_threads} threads for processing.')

    try:
        total_files = len([f for f in os.listdir(args.input) if os.path.isfile(os.path.join(args.input, f))])
        unique_bugs = process_files(args.input, crash_dir, clean_dir, max_threads)

        if unique_bugs and not stop.is_set():
            logging.info(f'Found {len(unique_bugs)} unique bugs across {total_files} files in total.')
            copy_unique_files(unique_bugs, unique_dir)
        elif stop.is_set():
            logging.warning(f'Process interrupted after {len(unique_bugs)} files were processed.')
    except KeyboardInterrupt:
        logging.warning('Interrupt received, exiting immediately...')
    finally:
        sys.exit(0)


if __name__ == '__main__':
    main()
