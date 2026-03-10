# -*- coding: utf-8 -*-
#!/usr/bin/env python

"""
SeedFilter is a Python script to group valid samples by file size and filter them based on their variability in a multi-threaded manner.

Example:
    python SeedFilter.py -i ./input_folder -o ./output_folder -v 30 -t 4 --bucket 8
"""

__author__    = 'Gabor Seljan'
__version__   = '0.2.1'
__date__      = '2026/02/17'
__copyright__ = 'Copyright (c) 2026 Gabor Seljan'
__license__   = 'MIT'

import os
import sys
import shutil
import random
import logging
import argparse

from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed

logging.basicConfig(
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S',
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('SeedFilter.log', mode='a'),
        logging.StreamHandler()
    ]
)

MAX_PER_GROUP   = 20  # cap selected files per size group
PREFILTER_BYTES = 64  # cheap prefilter


def calculate_variance(data1, data2):
    if len(data1) != len(data2):
        return 100.0
    differences = sum(abs(b1 - b2) for b1, b2 in zip(data1, data2))
    max_diff = len(data1) * 255
    return (differences / max_diff) * 100.0


def quick_difference(data1, data2, n=PREFILTER_BYTES):
    return sum(abs(a - b) for a, b in zip(data1[:n], data2[:n]))


def group_files_by_size(input_dir, bucket_size):
    size_groups = defaultdict(list)
    total = 0
    for root, _, files in os.walk(input_dir):
        for file in files:
            path = os.path.join(root, file)
            try:
                size = os.path.getsize(path)
                bucket = size // bucket_size
                size_groups[bucket].append(path)
                total += 1
            except OSError:
                logging.warning(f'Could not access file {path}.')
    logging.info(f'Found {total} files in total.')
    return size_groups, total


def filter_files_with_variance(group, threshold):
    filtered = []

    if len(group) < 2:
        return group[:1]

    data_cache = {}
    for file in group:
        try:
            with open(file, 'rb') as f:
                data_cache[file] = f.read()
        except OSError:
            logging.warning(f'Could not read file {file}.')

    files = list(data_cache.keys())
    random.shuffle(files)

    for file1 in files:
        data1 = data_cache[file1]
        unique = True

        for file2 in filtered:
            data2 = data_cache[file2]

            diff = quick_difference(data1, data2)
            if diff < threshold * PREFILTER_BYTES:
                variance = calculate_variance(data1, data2)
                if variance < threshold:
                    unique = False
                    break

        if unique:
            filtered.append(file1)

        if len(filtered) >= MAX_PER_GROUP:
            break

    return filtered


def process_size_group(bucket, group, variance, output_dir):
    logging.info(f'Processing size bucket {bucket} ({len(group)} files)')
    group = filter_files_with_variance(group, variance)

    for file in group:
        try:
            shutil.copy(file, output_dir)
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
    parser.add_argument('-b', '--bucket', type=int, default=30,
                        help='file size bucket width in bytes (defaults to 30)')

    args = parser.parse_args()

    if args.bucket <= 0:
        logging.error('Bucket size must be a positive integer.')
        sys.exit(1)

    if not os.path.isdir(args.input):
        logging.error(f'Input folder {args.input} does not exist or is not a directory!')
        sys.exit(1)

    os.makedirs(args.output, exist_ok=True)

    logging.info('Grouping files by approximate size...')
    size_groups, total_files = group_files_by_size(args.input, args.bucket)

    logging.info(f'{len(size_groups)} size buckets identified.')

    total_selected = 0
    with ThreadPoolExecutor(max_workers=args.threads) as executor:
        futures = []
        for bucket, files in size_groups.items():
            futures.append(
                executor.submit(process_size_group, bucket, files, args.variance, args.output)
            )

        for future in as_completed(futures):
            total_selected += future.result()

    logging.info(f'{total_selected} files selected and copied to {args.output}.')


if __name__ == '__main__':
    main()
