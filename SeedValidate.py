# -*- coding: utf-8 -*-
#!/usr/bin/env python

"""
SeedValidate is a Python script to validate EMF metafiles by using Paint to determine if the file can be opened successfully.

Example:
    python SeedValidate.py -i ./input_folder -o ./output_folder -e .emf
"""

__author__    = 'Gabor Seljan'
__version__   = '0.5.9'
__date__      = '2025/04/02'
__copyright__ = 'Copyright (c) 2025 Gabor Seljan'
__license__   = 'MIT'

import os
import sys
import time
import shutil
import signal
import hashlib
import logging
import argparse
import threading
import concurrent.futures

try:
    from pywinauto import timings
    from pywinauto.application import Application
    from pywinauto.findwindows import ElementNotFoundError
except ImportError as e:
    logging.error(f'Missing dependency: {e}')
    sys.exit(1)

stop = threading.Event()

logging.basicConfig(
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S',
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('SeedValidate.log', mode='w'),
        logging.StreamHandler()
    ]
)

print('''
           _____               ___      __   _ _     _       _
          / ____|    v{}   | \\ \\    / /  | (_)   | |     | |
         | (___   ___  ___  __| |\\ \\  / /_ _| |_  __| | __ _| |_ ___
          \\___ \\ / _ \\/ _ \\/ _` | \\ \\/ / _` | | |/ _` |/ _` | __/ _ \\
          ____) |  __/  __/ (_| |  \\  / (_| | | | (_| | (_| | ||  __/
         |_____/ \\___|\\___|\\__,_|   \\/ \\__,_|_|_|\\__,_|\\__,_|\\__\\___|
'''.format(__version__))

MAX_RETRIES = 3  # Number of retries for file operations
RETRY_DELAY = 2  # Delay (in seconds) between retries


def handle_exit_signal(signum, frame):
    if not stop.is_set():
        logging.warning('Interrupt received, setting stop event...')
        stop.set()


def calculate_hash(path):
    with open(path, 'rb') as file:
        data = file.read()
    return hashlib.sha256(data).hexdigest().upper()


def is_emf_valid_via_ui(file_path):
    timings.Timings.window_find_timeout = 10
    app = None
    try:
        app = Application(backend='uia').start(f'mspaint "{file_path}"', wait_for_idle=False)
        dlg = app.window(title='Paint cannot read this file.', enabled_only=True)

        if dlg.exists() or dlg.is_visible():
            return False  # File is explicitly invalid
    except ElementNotFoundError:
        return True
    except Exception as e:
        logging.error(f'Failed to start Paint for {file_path}: {e}')
        return False
    finally:
        if app is not None:
            try:
                app.kill()
            except Exception as e:
                logging.debug(f'Exception during app.kill() for {file_path}: {e}')
    return False


def is_file_accessible(file_path):
    return os.access(file_path, os.R_OK | os.W_OK)


def process_file(filename, args):
    result = {'processed': 0, 'valid': 0, 'invalid': 0, 'moved': 0, 'skipped': 0}

    if stop.is_set():  # Mark file as skipped if processing is interrupted before it starts
        result['skipped'] = 1
        return result

    result['processed'] = 1
    src = os.path.join(args.input, filename)

    if not is_emf_valid_via_ui(src):
        if stop.is_set():
            result['skipped'] = 1
            return result
        logging.warning(f'{filename} is NOT valid!')
        result['invalid'] = 1
        return result  # If invalid, stop processing immediately

    if stop.is_set():  # Ensure we do not continue after an interruption
        result['skipped'] = 1
        return result

    checksum = calculate_hash(src)
    dst = os.path.join(args.output, filename if filename.lower() == f'{checksum}{args.extension}'.lower() else f'{checksum}{args.extension}')
    logging.debug(f'Renaming {filename} to {os.path.basename(dst)}')

    for attempt in range(MAX_RETRIES):
        if stop.is_set():
            result['skipped'] = 1
            return result
        try:
            if not is_file_accessible(src):
                time.sleep(RETRY_DELAY)
                continue
            shutil.move(src, dst)
            if stop.is_set():
                result['skipped'] = 1
                return result
            result['moved'] = 1
            result['valid'] = 1
            logging.info(f'{filename} is VALID.')
            break
        except Exception as e:
            if attempt < MAX_RETRIES - 1:
                time.sleep(RETRY_DELAY)
            else:
                logging.error(f'Failed to process {filename} after {MAX_RETRIES} attempts: {e}')
                result['skipped'] = 1

    return result


def main():
    if os.name != 'nt':
        logging.error('This script is intended to run on Windows!')
        sys.exit(1)

    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description='Validate EMF metafiles by using Paint to determine if the file can be opened successfully.',
        prog='SeedValidate'
    )

    parser.add_argument('-i', '--input', type=str, required=True,
                        help='input folder containing unknown sample files')
    parser.add_argument('-o', '--output', type=str, required=True,
                        help='output folder to store valid sample files')
    parser.add_argument('-e', '--extension', type=str, default='.emf',
                        help='file extension to use for the valid samples (defaults to .emf)')
    parser.add_argument('-t', '--threads', type=int, default=None,
                        help='maximum number of threads for processing')
    parser.add_argument('-v', '--verbose', action='store_true',
                        help='enable verbose logging')

    args = parser.parse_args()

    if args.verbose:
        logging.getLogger().setLevel(logging.DEBUG)

    if not args.extension.startswith('.'):
        args.extension = f'.{args.extension}'

    if not os.path.isdir(args.input):
        logging.error(f'Input folder {args.input} does not exist or is not a directory!')
        sys.exit(1)

    os.makedirs(args.output, exist_ok=True)

    filenames = [
        f for f in os.listdir(args.input)
        if f.lower().endswith(args.extension) and os.path.isfile(os.path.join(args.input, f))
    ]

    if not filenames:
        logging.warning(f'No files with extension {args.extension} found in {args.input}!')
        sys.exit(0)

    signal.signal(signal.SIGINT, handle_exit_signal)

    max_threads = args.threads if args.threads else min(32, os.cpu_count() + 4)
    logging.info(f'Using {max_threads} threads for processing.')

    total = {'processed': 0, 'valid': 0, 'invalid': 0, 'moved': 0, 'skipped': 0}

    executor = concurrent.futures.ThreadPoolExecutor(max_workers=max_threads)
    futures = {executor.submit(process_file, filename, args): filename for filename in filenames}

    try:
        for future in concurrent.futures.as_completed(futures):
            if stop.is_set():
                break
            result = future.result()
            for key in total:
                total[key] += result.get(key, 0)
    except KeyboardInterrupt:
        stop.set()
    finally:
        executor.shutdown(wait=True)

        logging.info(f'Processed: {total['processed']}, Valid: {total['valid']}, '
                     f'Invalid: {total['invalid']}, Moved: {total['moved']}, Skipped: {total['skipped']}')

        sys.exit(1 if stop.is_set() else 0)


if __name__ == '__main__':
    main()
