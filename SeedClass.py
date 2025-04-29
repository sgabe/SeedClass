# -*- coding: utf-8 -*-
#!/usr/bin/env python

"""
SeedClass is an experimental machine learning project employing binary classification to predict whether fuzzing a specific seed file will lead to a vulnerability.
"""

__author__ = 'Gabor Seljan'
__version__ = '0.3'
__date__ = '2024/11/17'
__copyright__ = 'Copyright (c) 2025 Gabor Seljan'
__license__ = 'MIT'

import os
import sys
import heapq
import pyemf3
import numpy as np
import pandas as pd

from argparse import *
from shutil import copy
from base64 import b64encode
from datetime import datetime

from tensorflow.keras import Input
from tensorflow.keras.metrics import AUC
from tensorflow.keras.metrics import Recall
from tensorflow.keras.metrics import Precision
from tensorflow.keras.regularizers import L2
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout
from tensorflow.keras.callbacks import EarlyStopping

from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import KFold
from sklearn.model_selection import train_test_split


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

parser.add_argument('-N, --negative', dest='negative',
                    help='path to directory containing negative samples')
parser.add_argument('-P, --positive', dest='positive',
                    help='path to directory containing positive samples')
parser.add_argument('-U, --unknown', dest='unknown',
                    help='path to directory containing unknown samples')

parser.add_argument('-E, --encoding', dest='encoding', choices=['simple', 'product'], default='simple',
                    help='encoding method to use (simple or product)')
parser.add_argument('-V', dest='validation', action='store_true',
                    help='whether or not use cross-validation (default false)')
parser.add_argument('-R, --regularization', dest='regularization', action='store_true',
                    help='whether or not use L2 regularization (default false)')

parser.add_argument('--seed', dest='seed', type=int, default=None,
                    help='set initial seed (default none)')
parser.add_argument('--test-size', dest='test_size', type=float, default=0.2,
                    help='set test size (default 0.2)')
parser.add_argument('--batch-size', dest='batch_size', type=int, default=32,
                    help='set batch size (default 32)')
parser.add_argument('--learning-rate', dest='learning_rate', type=float, default=0.001,
                    help='set learning rate (default 0.001)')
parser.add_argument('--nsplits', dest='nsplits', type=int, default=4,
                    help='set n-splits (default 4)')
parser.add_argument('--epochs', dest='epochs', type=int, default=10,
                    help='set number of epochs (default 10)')
parser.add_argument('--threshold', dest='threshold', type=float, default=0.5,
                    help='set threshold (default 0.5)')

parser.add_argument('--split', dest='split',
                    help='split large metafile into smaller pieces')

parser.add_argument('--verbose', dest='verbose', action='store_true',
                    help='run in verbose mode')


args = parser.parse_args()


ENCODING          = args.encoding
VALIDATION        = args.validation
REGULARIZATION    = args.regularization

FEATURE_RANGE_MAX = 0.646464646464 if ENCODING == 'simple' else (pow(64, 6))/pow(10,11) # 0.68719476736
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

LABEL_NEGATIVE  = 0
LABEL_POSITIVE  = 1

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


def save_emf(records, index):
    new_emf = pyemf3.EMF(width=8, height=6)
    new_emf.records.extend(records)
    filename = f'output_{index}.emf'
    print(f'[*] Saving {filename}')
    new_emf.save(filename)


def split_emf(input_file, split_size):
    print(f'[*] Splitting {input_file} into {split_size} smaller pieces')

    e = pyemf3.EMF(verbose=VERBOSE)
    e.load(input_file)

    counter = 0
    records = []

    for record in e.records:
        if record.iType != 1:
            records.append(record)
        if len(records) == split_size:
            counter += 1
            save_emf(records, counter)
            records = []

    # Save any remaining records
    if records:
        counter += 1
        save_emf(records, counter)


def load_data(data, dir, label=LABEL_NEGATIVE):
  def process(path):

    # Normalize decimal numbers
    def scale(X):
      lst = list()
      for i in X:
        lst.append((i-min(X))/(max(X)-min(X)) * FEATURE_RANGE_MAX)
      return lst

    # Yield successive n-sized chunks from lst
    def chunks(lst, n):
      for i in range(0, len(lst), n):
        yield lst[i:i + n]

    encoded = list()
    with open(path, 'rb') as f:
      # Encode file as Base64 string
      for i in b64encode(f.read()):
        # Encode every single char as a decimal number
        encoded.append(CHARMAP[chr(i)])

    # Group every 6 number to a larger decimal
    decimal = list()
    for i in chunks(encoded, 6):
        if args.encoding == 'simple':
            decimal.append(int(''.join(map(str, i))))
        elif args.encoding == 'product':
            a = np.array(i)
            a = a[a != 0]
            p = np.prod(a)
            decimal.append(p)

    # Pad the list to 256 elements
    while len(decimal) < 256:
      decimal.append(0)
    return decimal

  good = []
  bad = []
  try:
    print('[*] Processing directory {} containing samples for label {}'.format(os.path.join(os.getcwd(), dir), label))
    for file in [f for f in os.listdir(os.path.join(os.getcwd(), dir)) if f.lower().endswith('.emf')]:
      features = process(os.path.join(os.getcwd(), dir, file))
      features[:0] = [label]
      if len(features) == 257: # Ignore too big files
        good.append(len(features))
        data.update({file: features})
      else:
        bad.append(len(features))
        print('[-] Ignoring {} which has {} features and is {} bytes'.format(file, len(features), os.path.getsize(os.path.join(os.getcwd(), dir, file))))
  except FileNotFoundError:
    print('[!] The system cannot find the path specified!')
  except Exception as e:
    print('[!] Something, somewhere went terribly wrong!')
    pass
  finally:
    print(f'[+] Good: {len(good)} - Bad: {len(bad)} - Ratio: {len(bad)/(len(bad)+len(good)) * 100:.2f}%')
    return data


def main():

    if args.split:
        split_emf(args.split, 2)
        sys.exit(0)

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
    print(f'[*] Loss: {scores[0] * 100:.2f}% - Precision: {scores[3] * 100:.2f}% - Recall: {scores[2] * 100:.2f}%')

    dd = {}
    if args.unknown:
        dd = load_data(dd, args.unknown)

    df = pd.DataFrame.from_dict(dd, orient='index').add_prefix('f')

    X_pred = df.drop('f0', axis=1).values
    X_pred = pd.DataFrame(scaler.transform(X_pred))

    preds = (model.predict(X_pred, verbose=VERBOSE) > THRESHOLD).astype('int32')
    indices = []

    if np.count_nonzero(preds) == 0:
        print(f'[*] Automatically adjusting threshold for finding best candidates')
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

    lst = list()
    for idx, l in np.ndenumerate(preds):
        if l == 1:
            if indices and idx[0] not in indices:
                continue
            lst.append(df.index[idx[0]])
        if len(lst) == 20:
            break

    print(f'[*] Selected {len(lst)} files out of {len(X_pred)} total')

    try:
        for filename in lst:
            print('{}'.format(filename))
    except:
        print('[!] Something, somewhere went terribly wrong!')
        pass


if __name__ == '__main__':
    main()
