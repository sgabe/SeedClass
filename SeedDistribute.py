# -*- coding: utf-8 -*-
#!/usr/bin/env python

"""
SeedDistribute is a Python script to process a SeedSort log file and distribute crash samples based on bug occurrences.

Example:
    python SeedDistribute.py -l log_file -i ./input_folder -o ./output_folder -s size
"""

__author__    = 'Gabor Seljan'
__version__   = '0.4.3'
__date__      = '2025/04/25'
__copyright__ = 'Copyright (c) 2025 Gabor Seljan'
__license__   = 'MIT'

import os
import re
import sys
import shutil
import logging
import argparse

from collections import defaultdict

logging.basicConfig(
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S',
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('SeedDistribute.log', mode='w'),
        logging.StreamHandler()
    ]
)

print('''
           _____               _ _____  _     _        _ _           _
          / ____|    v{}   | |  __ \\(_)   | |      (_) |         | |
         | (___   ___  ___  __| | |  | |_ ___| |_ _ __ _| |__  _   _| |_ ___
          \\___ \\ / _ \\/ _ \\/ _` | |  | | / __| __| '__| | '_ \\| | | | __/ _ \\
          ____) |  __/  __/ (_| | |__| | \\__ \\ |_| |  | | |_) | |_| | ||  __/
         |_____/ \\___|\\___|\\__,_|_____/|_|___/\\__|_|  |_|_.__/ \\__,_|\\__\\___|
'''.format(__version__))


def process_log(path, input_dir, output_dir=None, distribution_size=100):
    samples = defaultdict(list)  # Maps Bug ID to list of files
    bugs = {}  # Maps Bug ID to (Function name, Library name)
    optimized_counts = defaultdict(int)

    pattern = re.compile(
        r'File (\S+) with (\d+) bytes triggered bug (\S+) in (\S+) within (\S+)\.'
    )

    try:
        with open(path, 'r') as file:
            for line in file:
                match = pattern.search(line)
                if match:
                    sample, _, id, function, library = match.groups()
                    samples[id].append(sample)
                    bugs[id] = (function, library)
    except FileNotFoundError:
        logging.error(f'Log file {path} not found!')
        return

    if output_dir:
        os.makedirs(output_dir, exist_ok=True)

        for id, files in samples.items():
            total_count = len(files)
            target_count = min(distribution_size, total_count)
            copied_files = 0

            for file in files[:target_count]:
                src_path = os.path.join(input_dir, file)
                dest_path = os.path.join(output_dir, file)
                if os.path.exists(src_path):
                    shutil.copy(src_path, dest_path)
                    optimized_counts[id] += 1
                    copied_files += 1
                    if copied_files >= target_count:
                        break

        logging.info('Statistics for optimized collection:')
        for id, count in sorted(optimized_counts.items(), key=lambda x: x[1], reverse=True):
            function, library = bugs[id]
            logging.info(f"{count:6} Bug ID: {id:12} Function: {function:40} Library: {library:20}")
    else:
        logging.info('Summary of bugs identified in the crash samples:')
        sorted_summary = sorted(
            [(len(files), id) for id, files in samples.items()],
            reverse=True
        )
        for count, id in sorted_summary:
            function, library = bugs[id]
            logging.info(f'Count: {count:<6} ID: {id:<12} Function: {function:<40} Library: {library:<20}')

        logging.debug('List of crash samples for each bug:')
        for id, files in samples.items():
            function, library = bugs[id]
            logging.debug(f'Bug ID: {id:<12} Function: {function:<40} Library: {library:<20}')
            for file in files:
                logging.debug(f"\t{file}")


def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description='Process a log file and optimize bug distribution across files.',
        prog='SeedDistribute'
    )

    parser.add_argument('-l', '--log', required=True,
                        help='path to the SeedSort log file')
    parser.add_argument('-i', '--input', required=True,
                        help='input folder where the crash samples are located')
    parser.add_argument('-o', '--output',
                        help='output folder to save crash samples for optimized bug distribution')
    parser.add_argument('-s', '--size', type=int, default=100,
                        help='target size for bug distribution')
    parser.add_argument('--verbose', action='store_true',
                        help='enable verbose logging')

    args = parser.parse_args()

    if not os.path.exists(args.input) or not os.path.isdir(args.input):
        logging.error(f'Input folder {args.input} does not exist or is not a directory!')
        sys.exit(1)

    if args.verbose:
        logging.getLogger().setLevel(logging.DEBUG)

    process_log(args.log, args.input, args.output, args.size)


if __name__ == '__main__':
    main()
