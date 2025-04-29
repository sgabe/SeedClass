# -*- coding: utf-8 -*-
#!/usr/bin/env python

"""
SeedClass is an experimental machine learning project employing binary classification to predict whether fuzzing a specific seed file will lead to a vulnerability.
"""

__author__    = 'Gabor Seljan'
__version__   = '0.4'
__date__      = '2025/04/02'
__copyright__ = 'Copyright (c) 2025 Gabor Seljan'
__license__   = 'MIT'

import os
import sys
import heapq
import logging
import numpy as np
import pandas as pd

from shutil import copy
from base64 import b64encode
from datetime import datetime

from tensorflow.keras import Input
from tensorflow.keras.regularizers import L2
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout
from tensorflow.keras.callbacks import EarlyStopping
from tensorflow.keras.metrics import AUC, Recall, Precision

from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import KFold, train_test_split

from argparse import ArgumentParser, RawDescriptionHelpFormatter

logging.basicConfig(
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S',
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('SeedClass.log', mode='w'),
        logging.StreamHandler()
    ]
)

print('''

                   _____               _  _____ _
                  / ____|             | |/ ____| |      v{}
                 | (___   ___  ___  __| | |    | | __ _ ___ ___
                  \\___ \\ / _ \\/ _ \\/ _` | |    | |/ _` / __/ __|
                  ____) |  __/  __/ (_| | |____| | (_| \\__ \\__ \\
                 |_____/ \\___|\\___|\\__,_|\\_____|_|\\__,_|___/___/

'''.format(__version__))


parser = ArgumentParser(
    formatter_class=RawDescriptionHelpFormatter,
    description=__doc__,
    prog='seedclass'
)

parser.add_argument('-N', '--negative', dest='negative',
                    help='Path to directory containing negative samples')
parser.add_argument('-P', '--positive', dest='positive',
                    help='Path to directory containing positive samples')
parser.add_argument('-U', '--unknown', dest='unknown',
                    help='Path to directory containing unknown samples')

parser.add_argument('-E', '--encoding', dest='encoding', choices=['simple', 'product'], default='simple',
                    help='Encoding method to use (simple or product)')
parser.add_argument('-V', '--validation', dest='validation', action='store_true',
                    help='Whether or not use cross-validation (default false)')
parser.add_argument('-R', '--regularization', dest='regularization', action='store_true',
                    help='Whether or not use L2 regularization (default false)')

parser.add_argument('--seed', dest='seed', type=int, default=None,
                    help='Set initial seed (default none)')
parser.add_argument('--test-size', dest='test_size', type=float, default=0.2,
                    help='Set test size (default 0.2)')
parser.add_argument('--batch-size', dest='batch_size', type=int, default=32,
                    help='Set batch size (default 32)')
parser.add_argument('--learning-rate', dest='learning_rate', type=float, default=0.001,
                    help='Set learning rate (default 0.001)')
parser.add_argument('--nsplits', dest='nsplits', type=int, default=4,
                    help='Set n-splits (default 4)')
parser.add_argument('--epochs', dest='epochs', type=int, default=10,
                    help='Set number of epochs (default 10)')
parser.add_argument('--threshold', dest='threshold', type=float, default=0.5,
                    help='Set threshold (default 0.5)')


parser.add_argument('--verbose', dest='verbose', action='store_true',
                    help='Run in verbose mode')


args = parser.parse_args()


ENCODING          = args.encoding
VALIDATION        = args.validation
REGULARIZATION    = args.regularization

FEATURE_RANGE_MAX_SIMPLE = 0.646464646464
FEATURE_RANGE_MAX_PRODUCT = (pow(64, 6)) / pow(10, 11) # 0.68719476736

FEATURE_RANGE_MAX = FEATURE_RANGE_MAX_SIMPLE if ENCODING == 'simple' else FEATURE_RANGE_MAX_PRODUCT
TEST_SIZE         = args.test_size            # Default is 0.25
BATCH_SIZE        = args.batch_size           # Default is 32
LEARNING_RATE     = args.learning_rate        # Default is 0.001
SEED              = args.seed                 # Default is None
N_SPLITS          = args.nsplits              # Default is 4
EPOCHS            = args.epochs               # Default is 10
VERBOSE           = args.verbose              # Default is 0

# Increase for lower FP and higher precision yielding less files.
# Decrease for lower FN and higher recall yielding more files.
THRESHOLD         = args.threshold            # Default is 0.50

LABEL_NEGATIVE    = 0
LABEL_POSITIVE    = 1

CHARMAP           = {
    "A":64, "N":13, "a":26, "n":39, "0":52,
    "B":1,  "O":14, "b":27, "o":40, "1":53,
    "C":2,  "P":15, "c":28, "p":41, "2":54,
    "D":3,  "Q":16, "d":29, "q":42, "3":55,
    "E":4,  "R":17, "e":30, "r":43, "4":56,
    "F":5,  "S":18, "f":31, "s":44, "5":57,
    "G":6,  "T":19, "g":32, "t":45, "6":58,
    "H":7,  "U":20, "h":33, "u":46, "7":59,
    "I":8,  "V":21, "i":34, "v":47, "8":60,
    "J":9,  "W":22, "j":35, "w":48, "9":61,
    "K":10, "X":23, "k":36, "x":49, "+":62,
    "L":11, "Y":24, "l":37, "y":50, "/":63,
    "M":12, "Z":25, "m":38, "z":51, "=":0,
}


def load_data(data, dir, label=LABEL_NEGATIVE):




    def process(path):
        # Normalize decimal numbers.
        def scale(X):
            return [(i - min(X)) / (max(X) - min(X)) * FEATURE_RANGE_MAX for i in X]

        # Yield successive n-sized chunks from a list.
        def chunks(lst, n):
            return [lst[i:i + n] for i in range(0, len(lst), n)]

        with open(path, 'rb') as f:
            data = f.read()
        # Encode file content via Base64 and map each byte using CHARMAP.
        encoded = [CHARMAP.get(chr(i), 0) for i in b64encode(data)]

        # Group every 6 numbers into a single decimal feature.
        decimal = [
            np.prod(np.array(chunk)[np.array(chunk) != 0]) if ENCODING == 'product'
            else int(''.join(map(str, chunk)))
            for chunk in chunks(encoded, 6)
        ]

        # Pad the feature list to 256 elements.
        while len(decimal) < 256:
            decimal.append(0)
        return decimal

    good, bad = [], []
    try:
        logging.info(f'Processing directory {os.path.join(os.getcwd(), dir)} containing samples for label {label}')
        for file in [f for f in os.listdir(os.path.join(os.getcwd(), dir)) if f.lower().endswith('.emf')]:
            features = process(os.path.join(os.getcwd(), dir, file))
            features.insert(0, label)
            if len(features) == 257: # Ignore too big files
                good.append(len(features))
                data.update({file: features})
            else:
                bad.append(len(features))
                logging.warning(f'Ignoring {file} which has {len(features)} features and is {os.path.getsize(os.path.join(os.getcwd(), dir, file))} bytes')
    except FileNotFoundError:
        logging.error('The system cannot find the specified path!')
    except Exception as e:
        logging.error(f'Something, somewhere went terribly wrong! Error: {e}')
        pass
    finally:
        total = len(good) + len(bad)
        ratio = (len(bad) / total * 100) if total > 0 else 0
        logging.info(f'Good: {len(good)} - Bad: {len(bad)} - Ratio: {ratio:.2f}%')
        return data


def main():




    dd = {}
    if args.negative:
        dd = load_data(dd, args.negative, LABEL_NEGATIVE)
    if args.positive:
        dd = load_data(dd, args.positive, LABEL_POSITIVE)

    df = pd.DataFrame.from_dict(dd, orient='index').add_prefix('f')

    X = df.drop('f0', axis=1).values
    y = df['f0'].values

    X_train, X_test, y_train, y_test = train_test_split(X, y,
        test_size=TEST_SIZE,
        random_state=SEED,
        shuffle=True)

    scaler = MinMaxScaler(feature_range=(0, FEATURE_RANGE_MAX))
    X_train = pd.DataFrame(scaler.fit_transform(X_train)).values
    X_test = pd.DataFrame(scaler.transform(X_test)).values

    model = Sequential()
    model.add(Input(shape=(256,)))
    model.add(Dense(256, activation='relu', kernel_regularizer=L2(0.00001) if REGULARIZATION else None))
    model.add(Dropout(0.5))
    model.add(Dense(256, activation='relu', kernel_regularizer=L2(0.00001) if REGULARIZATION else None))
    model.add(Dropout(0.5))
    model.add(Dense(1, activation='sigmoid'))

    model.compile(
        optimizer='adam',
        loss='binary_crossentropy',
        metrics=['accuracy',
            Recall(thresholds=THRESHOLD, name='recall'),
            Precision(thresholds=THRESHOLD, name='precision'),
        ]
    )

    if VALIDATION:
        histories = []
        kfold = KFold(n_splits=N_SPLITS, shuffle=True)
        for train, test in kfold.split(X_train, y_train):
            history = model.fit(
                x=X_train[train],
                y=y_train[train],
                batch_size=BATCH_SIZE,
                epochs=EPOCHS,
                verbose=VERBOSE,
                validation_data=(X_train[test], y_train[test]),
                callbacks=[
                    EarlyStopping(monitor='val_loss', mode='min', restore_best_weights=True),
                ]
            )
            histories.append(history)
    else:
        history = model.fit(
            x=X_train,
            y=y_train,
            batch_size=BATCH_SIZE,
            epochs=EPOCHS,
            verbose=VERBOSE,
            validation_data=(X_test, y_test),
            callbacks=[
                EarlyStopping(monitor='val_loss', mode='min', restore_best_weights=True),
            ]
        )

    scores = model.evaluate(X_test, y_test, verbose=VERBOSE)
    logging.info(f'Loss: {scores[0] * 100:.2f}% - Recall: {scores[2] * 100:.2f}% - Precision: {scores[3] * 100:.2f}%')

    dd = {}
    if args.unknown:
        dd = load_data(dd, args.unknown)

    df = pd.DataFrame.from_dict(dd, orient='index').add_prefix('f')

    X_pred = df.drop('f0', axis=1).values
    X_pred = pd.DataFrame(scaler.transform(X_pred))

    preds = (model.predict(X_pred, verbose=VERBOSE) > THRESHOLD).astype('int32')
    indices = []

    if np.count_nonzero(preds) == 0:
        consent = input('No positive predictions found. Automatically adjust threshold? (yes/no): ').strip().lower()
        if consent in ['yes', 'y']:
            logging.info('Automatically adjusting threshold for finding best candidates')
            best = []
            uniques = set()

            preds = model.predict(X_pred, verbose=VERBOSE)

            flats = [item for sublist in preds for item in sublist]
            for v in heapq.nlargest(len(flats), flats):
                if v not in uniques:
                    uniques.add(v)
                    best.append(v)
                if len(best) == 21:
                    break

            indices = [flats.index(v) for v in best]

            preds = (preds > min(best)).astype('int32')
        else:
            logging.error('Threshold adjustment skipped. Predictions might not include the best candidates.')

    lst = list()
    for idx, l in np.ndenumerate(preds):
        if l == 1:
            if indices and idx[0] not in indices:
                continue
            lst.append(df.index[idx[0]])
        if len(lst) == 20:
            break

    logging.info(f'Selected {len(lst)} files out of {len(X_pred)} total')

    try:
        for filename in lst:
            logging.info(filename)
    except:
        logging.error('Something, somewhere went terribly wrong!')
        pass


if __name__ == '__main__':
    main()
