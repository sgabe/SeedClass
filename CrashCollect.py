# -*- coding: utf-8 -*-
#!/usr/bin/env python

"""
CrashCollect is a Python script to gather unique crash samples from the output directories of multiple WinAFL fuzzer instances.

Example:
    python CrashCollect.py -i ./input_folder -o ./output_folder
"""

__author__    = 'Gabor Seljan'
__version__   = '0.3.0'
__date__      = '2025/11/09'
__copyright__ = 'Copyright (c) 2025 Gabor Seljan'
__license__   = 'MIT'

import os
import re
import sys
import shutil
import hashlib
import logging
import argparse

logging.basicConfig(
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S',
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('CrashCollect.log', mode='a'),
        logging.StreamHandler()
    ]
)

print('''
                  _____               _      _____      _ _           _
                 / ____|    v{}   | |    / ____|    | | |         | |
                | |     _ __ __ _ ___| |__ | |     ___ | | | ___  ___| |_
                | |    | '__/ _` / __| '_ \| |    / _ \| | |/ _ \/ __| __|
                | |____| | | (_| \__ \ | | | |___| (_) | | |  __/ (__| |_
                 \_____|_|  \__,_|___/_| |_|\_____\___/|_|_|\___|\___|\__|
'''.format(__version__))


def calculate_hash(path):
    with open(path, 'rb') as file:
        data = file.read()
    return hashlib.sha256(data).hexdigest().upper()


def is_valid_crash(filename):
    return re.match(r'^id_\d{6}_([0-9A-Fa-f]{8}_)?.+$', filename) is not None


def process_folder(input_path, output_path, extension, do_queue):
    count = 0

    for root, dirs, files in os.walk(input_path):
        if 'crashes' in dirs:
            crashes = os.path.join(root, 'crashes')
            logging.info(f'Processing crashes folder {crashes}...')

            for crash in os.listdir(crashes):
                if is_valid_crash(crash):
                    source = os.path.join(crashes, crash)
                    if os.path.isfile(source):
                        hash = calculate_hash(source)
                        destination = os.path.join(output_path, f'{hash}{extension}')
                        if not os.path.exists(destination):
                            shutil.copy2(source, destination)
                            count += 1

            bucket = os.path.join(crashes, 'bucket')
            if os.path.exists(bucket):
                logging.info(f'Processing bucket folder {bucket}...')
                for crash in os.listdir(bucket):
                    if is_valid_crash(crash):
                        source = os.path.join(bucket, crash)
                        if os.path.isfile(source):
                            hash = calculate_hash(source)
                            destination = os.path.join(output_path, f'{hash}{extension}')
                            if not os.path.exists(destination):
                                shutil.copy2(source, destination)
                                count += 1

        if do_queue and 'queue' in dirs:
            queue = os.path.join(root, 'queue')
            logging.info(f'Processing queue folder {queue}...')
            for sample in os.listdir(queue):
                source = os.path.join(queue, sample)
                if os.path.isfile(source):
                    hash = calculate_hash(source)
                    destination = os.path.join(output_path, f'{hash}{extension}')
                    if not os.path.exists(destination):
                        shutil.copy2(source, destination)
                        count += 1

    return count


def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description='Recursively collects unique crash samples from an output directory of a WinAFL fuzzer instance.',
        prog='CrashCollect'
    )

    parser.add_argument('-i', '--input', required=True,
                        help='input folder containing crash samples to process')
    parser.add_argument('-o', '--output', required=True,
                        help='output folder to copy unique crash samples')
    parser.add_argument('-e', '--extension', default='.emf',
                        help='file extension for crash samples (defaults to .emf)')
    parser.add_argument('-q', '--queue', action='store_true',
                        help='also process mutated files from the queue folder')

    args = parser.parse_args()

    if not os.path.isdir(args.input):
        logging.error(f'Input folder {args.input} does not exist or is not a directory!')
        sys.exit(1)

    os.makedirs(args.output, exist_ok=True)

    copied_files = process_folder(args.input, args.output, args.extension, args.queue)
    logging.info(f'Copied {copied_files} in total.')


if __name__ == '__main__':
    main()
