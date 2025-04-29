# -*- coding: utf-8 -*-
#!/usr/bin/env python

"""
SeedGroup is a Python script to randomly distribute seed files into groups.

Example:
    python SeedGroup.py -i ./input_folder -o ./output_folder -s 1000 -g 1
"""

__author__    = 'Gabor Seljan'
__version__   = '0.9.2'
__date__      = '2025/04/29'
__copyright__ = 'Copyright (c) 2025 Gabor Seljan'
__license__   = 'MIT'

import os
import sys
import random
import shutil
import logging
import argparse

logging.basicConfig(
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S',
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('SeedGroup.log', mode='w'),
        logging.StreamHandler()
    ]
)

print('''
                   _____               _  _____
                  / ____|    v{}   | |/ ____|
                 | (___   ___  ___  __| | |  __ _ __ ___  _   _ _ __
                  \\___ \\ / _ \\/ _ \\/ _` | | |_ | '__/ _ \\| | | | '_ \\
                  ____) |  __/  __/ (_| | |__| | | | (_) | |_| | |_) |
                 |_____/ \\___|\\___|\\__,_|\\_____|_|  \\___/ \\__,_| .__/
                                                               | |
                                                               |_|
'''.format(__version__))

def create_random_groups(input_dir, output_dir, num_files, num_groups):
    files = [f for f in os.listdir(input_dir) if os.path.isfile(os.path.join(input_dir, f))]
    count = len(files)
    logging.info(f'Found {count} files in {input_dir}.')

    if count == 0:
        logging.error(f'No files found in {input_dir}. Ensure the folder contains valid files.')
        sys.exit(1)

    needed = num_groups * num_files

    if count < needed:
        logging.warning(f'Not enough files available ({count}), selecting all.')
        needed = count
        num_files = min(num_files, count)


    selected = random.sample(files, needed)
    random.shuffle(selected)

    os.makedirs(output_dir, exist_ok=True)

    groups = [selected[i:i + num_files] for i in range(0, len(selected), num_files)]

    if num_groups == 1:
        for file in groups[0]:
            shutil.copy(os.path.join(input_dir, file), os.path.join(output_dir, file))
        logging.info(f'Copied {len(groups[0])} files directly into {output_dir}.')
    else:
        for i, group in enumerate(groups, 1):
            dir_path = os.path.join(output_dir, f'group{i}')
            os.makedirs(dir_path, exist_ok=True)
            for file in group:
                shutil.copy(os.path.join(input_dir, file), os.path.join(dir_path, file))
            logging.info(f'Group {i} created with {len(group)} files in {dir_path}.')

    logging.info(f'Successfully processed {num_groups} groups in {output_dir}.')


def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description='Randomly distribute seed files into groups.',
        prog='SeedGroup'
    )

    parser.add_argument('-i', '--input', required=True,
                        help='input folder containing valid seed files')
    parser.add_argument('-o', '--output', required=True,
                        help='output folder where the grouped files will be copied')
    parser.add_argument('-s', '--size', type=int, required=True,
                        help='number of seed files per group')
    parser.add_argument('-g', '--groups', type=int, required=True,
                        help='total number of groups to create')

    args = parser.parse_args()

    if not os.path.exists(args.input) or not os.path.isdir(args.input):
        logging.error(f'Input folder {args.input} does not exist or is not a directory!')
        sys.exit(1)

    if args.groups <= 0 or args.size <= 0:
        logging.error(f'Invalid group ({args.groups}) or size ({args.size}) parameter.')
        sys.exit(1)

    logging.info(f'Processing folder {args.input} to create {args.groups} group(s) of {args.size} files each in {args.output}.')

    try:
        create_random_groups(args.input, args.output, args.size, args.groups)
    except Exception as e:
        logging.error(f'An error occurred: {e}')


if __name__ == '__main__':
    main()
