# -*- coding: utf-8 -*-
#!/usr/bin/env python

"""
SeedSplit is a Python script to split EMF metafiles into smaller pieces based on the specified number of records.

Example:
    python SeedSplit.py -i input.emf -o output_folder -e .emf -p 24
"""

__author__    = 'Gabor Seljan'
__version__   = '0.4.1'
__date__      = '2025/04/02'
__copyright__ = 'Copyright (c) 2025 Gabor Seljan'
__license__   = 'MIT'

import os
import sys
import pyemf3
import random
import shutil
import logging
import hashlib
import argparse

logging.basicConfig(
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S',
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('SeedSplit.log', mode='w'),
        logging.StreamHandler()
    ]
)

print('''
                   _____               _  _____       _ _ _
                  / ____|    v{}   | |/ ____|     | (_) |
                 | (___   ___  ___  __| | (___  _ __ | |_| |_
                  \\___ \\ / _ \\/ _ \\/ _` |\\___ \\| '_ \\| | | __|
                  ____) |  __/  __/ (_| |____) | |_) | | | |_
                 |_____/ \\___|\\___|\\__,_|_____/| .__/|_|_|\\__|
                                               | |
                                               |_|
'''.format(__version__))


def calculate_hash(path):
    with open(path, 'rb') as file:
        data = file.read()
    return hashlib.sha256(data).hexdigest().upper()


def save_emf(records, output, extension, index):
    filename = f'id_{index:06d}{extension}'
    logging.debug(f'Saving piece {filename} with {len(records)} records')
    try:
        emf = pyemf3.EMF(width=random.randint(0, 12), height=random.randint(0, 6))
        emf.records.extend(records)
        emf.save(os.path.join(output, filename))
    except Exception as e:
        logging.error(f'Failed to save piece {filename}: {e}')
        raise


def filter_emf(output, extension):
    files = [f for f in os.listdir(output) if f.endswith(extension)]
    for file in sorted(files):
        old_path = os.path.join(output, file)
        checksum = calculate_hash(old_path)
        new_path = os.path.join(output, f'{checksum}{extension}')
        if os.path.exists(new_path):
            os.remove(old_path)
        else:
            os.rename(old_path, new_path)
    unique = len([f for f in os.listdir(output) if f.endswith(extension)])
    logging.info(f'Found {unique} unique pieces in {os.path.basename(output)}.')


def split_emf(input_file, output, extension, pieces):
    logging.info(f'Splitting {os.path.basename(input_file)} into pieces with {pieces} records each.')
    try:
        emf = pyemf3.EMF(verbose=False)
        emf.load(input_file)
    except Exception as e:
        logging.debug(f'Failed to load EMF file {os.path.basename(input_file)}: {e}')

    if not emf.records:
        logging.warning(f'No records found in EMF file {os.path.basename(input_file)}. Nothing to split.')

    logging.info(f'Found {len(emf.records)} total records in {os.path.basename(input_file)}.')

    records = []
    index = 1
    for record in emf.records:
        if record.iType != 1:  # Exclude header records
            records.append(record)
        if len(records) == pieces:
            save_emf(records, output, extension, index)
            index += 1
            records = []

    if records:
        save_emf(records, output, extension, index)

    filter_emf(output, extension)


def process_emf(file_path, output_base, extension, pieces):
    checksum = calculate_hash(file_path)
    file_dir = os.path.dirname(os.path.abspath(file_path))
    if os.path.abspath(file_dir) == os.path.abspath(output_base):
        output_folder = os.path.join(file_dir, checksum)
    else:
        output_folder = output_base

    os.makedirs(output_folder, exist_ok=True)

    success = True
    try:
        split_emf(file_path, output_folder, extension, pieces)
    except Exception as e:
        logging.error(f'Error processing file {os.path.basename(file_path)}: {e}')
        success = False

    total = len([f for f in os.listdir(output_folder) if f.endswith(extension)])
    if total < 10:
        shutil.rmtree(output_folder)
        new_name = f'{checksum}.discarded{extension}'
    elif success:
        new_name = f'{checksum}.splitted{extension}'
    else:
        new_name = f'{checksum}.skipped{extension}'

    new_path = os.path.join(file_dir, new_name)
    try:
        os.rename(file_path, new_path)
        logging.info(f'Processed and renamed file {os.path.basename(file_path)} to {os.path.basename(new_path)}')
    except Exception as e:
        logging.debug(f'Failed to rename file {os.path.basename(file_path)} to {os.path.basename(new_path)}: {e}')


def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description="Split EMF metafiles into smaller pieces. Supports processing a single file or all files in a directory.",
        prog="SeedSplit"
    )

    parser.add_argument('-i', '--input', type=str, required=True,
                        help='input EMF file or directory to process')
    parser.add_argument('-o', '--output', type=str, default='output',
                        help='output folder to save the split files')
    parser.add_argument('-e', '--extension', type=str, default='.emf',
                        help='file extension for the split files (defaults to .emf)')
    parser.add_argument('-p', '--pieces', type=int, default=20,
                        help='number of records per split file (defaults to 20)')
    parser.add_argument('--verbose', action='store_true',
                        help='enable verbose logging')

    args = parser.parse_args()

    if args.verbose:
        logging.getLogger().setLevel(logging.DEBUG)

    if not os.path.exists(args.input):
        logging.error(f'Input file or directory {args.input} does not exist!')
        sys.exit(1)

    if os.path.isdir(args.input):
        for file in os.listdir(args.input):
            file_path = os.path.join(args.input, file)
            if os.path.isfile(file_path):
                process_emf(file_path, args.input, args.extension, args.pieces)
    else:
        process_emf(args.input, args.output, args.extension, args.pieces)


if __name__ == '__main__':
    main()
