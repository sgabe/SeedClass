# -*- coding: utf-8 -*-
#!/usr/bin/env python

"""
SeedFilter is a Python script to group valid samples by file size and filter them based on their variability in a multi-threaded manner.

Example:
    python SeedFilter.py -i ./input_folder -o ./output_folder -v 30 -t 4
"""

__author__    = 'Gabor Seljan'
__version__   = '0.1.5'
__date__      = '2025/04/25'
__copyright__ = 'Copyright (c) 2025 Gabor Seljan'
__license__   = 'MIT'

import os
import sys
import shutil
import logging
import argparse

from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed

logging.basicConfig(
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S',
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('SeedFilter.log', mode='w'),
        logging.StreamHandler()
    ]
)


def calculate_variance(data1, data2):
    if len(data1) != len(data2):
        return 100
    differences = sum(abs(b1 - b2) for b1, b2 in zip(data1, data2))
    max_diff = len(data1) * 255
    return (differences / max_diff) * 100


def group_files_by_size(input_dir):
    size_groups = defaultdict(list)
    total = 0
    for root, _, files in os.walk(input_dir):
        for file in files:
            path = os.path.join(root, file)
            try:
                size = os.path.getsize(path)
                size_groups[size].append(path)
                total += 1
            except OSError:
                logging.warning(f'Could not access file {path}.')
    logging.info(f'Found {total} files in total.')
    return size_groups, total


def filter_files_with_variance(group, threshold=30):
    filtered = []

    if len(group) == 1:
        return filtered

    for i, file1 in enumerate(group):
        try:
            with open(file1, 'rb') as f1:
                data1 = f1.read()
            unique = True
            for file2 in filtered:
                with open(file2, 'rb') as sf:
                    data2 = sf.read()
                variance = calculate_variance(data1, data2)
                if variance < threshold:
                    unique = False
                    break
            if unique:
                filtered.append(file1)
        except OSError:
            logging.warning(f'Could not process file {file1}.')
    return filtered


def process_size_group(size, group, variance, output_dir):
    logging.info(f'Processing group of size {size} bytes with {len(group)} files.')
    group = filter_files_with_variance(group, threshold=variance)
    for file in group:
        try:
            shutil.copy(file, output_dir)
            logging.info(f'Copied file {file} to {output_dir}.')
        except OSError:
            logging.error(f'Failed to copy file {file} to {output_dir}.')
    return len(group)


def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description='Group and filter samples based on file size and variance using multithreading.',
        prog='SeedFilter'
    )

    parser.add_argument('-i', '--input', required=True,
                        help='input folder containing all samples')
    parser.add_argument('-o', '--output', required=True,
                        help='output folder to store the selected samples')
    parser.add_argument('-v', '--variance', type=float, default=30,
                        help='variance threshold (defaults to 30)')
    parser.add_argument('-t', '--threads', type=int, default=4,
                        help='number of threads to use (defaults to 4)')

    args = parser.parse_args()

    if not os.path.exists(args.input) or not os.path.isdir(args.input):
        logging.error(f'Input folder {args.input} does not exist or is not a directory!')
        sys.exit(1)

    os.makedirs(args.output, exist_ok=True)

    logging.info('Starting to group files by size...')
    size_groups, total_files = group_files_by_size(args.input)
    logging.info(f"{len(size_groups)} size groups identified:")
    for size, files in size_groups.items():
        logging.info(f'Group of size {size} bytes contains {len(files)} files.')

    total = 0
    with ThreadPoolExecutor(max_workers=args.threads) as executor:
        futures = []
        for size, files in size_groups.items():
            logging.info(f'Submitting group of size {size} bytes for processing.')
            futures.append(executor.submit(
                process_size_group, size, files, args.variance, args.output))
        for future in as_completed(futures):
            total += future.result()

    logging.info(f'{total} files selected have been copied to {args.output}.')


if __name__ == '__main__':
    main()
