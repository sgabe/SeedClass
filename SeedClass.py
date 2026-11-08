# -*- coding: utf-8 -*-
#!/usr/bin/env python

"""
SeedClass is an experimental machine learning project employing binary classification to predict whether fuzzing a specific seed file will lead to a vulnerability.

Example:
    python SeedClass.py -N ./negative.zip -P ./positive.zip -U ./unknown.zip --epochs 20 --batch-size 64 --learning-rate 0.0005 --validation --verbose
"""

__author__    = 'Gabor Seljan'
__version__   = '0.6.5'
__date__      = '2026/11/08'
__copyright__ = 'Copyright (c) 2026 Gabor Seljan'
__license__   = 'MIT'

import io
import os
import sys
import onnx
import logging
import tf2onnx
import numpy as np
import pandas as pd
import tensorflow as tf

from shutil import copyfileobj
from zipfile import ZipFile
from base64 import b64encode

from tensorflow.keras import Input
from tensorflow.keras.regularizers import L2
from tensorflow.keras.models import Sequential
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.layers import Dense, Dropout
from tensorflow.keras.callbacks import EarlyStopping
from tensorflow.keras.metrics import AUC, BinaryAccuracy, Recall, Precision
from tensorflow.keras.metrics import TruePositives, TrueNegatives
from tensorflow.keras.metrics import FalsePositives, FalseNegatives

from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import StratifiedKFold, train_test_split

from argparse import ArgumentParser, RawDescriptionHelpFormatter

logging.basicConfig(
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S',
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('SeedClass.log', mode='a'),
        logging.StreamHandler()
    ]
)

print('''

                   _____               _  _____ _
                  / ____|             | |/ ____| |    v{}
                 | (___   ___  ___  __| | |    | | __ _ ___ ___
                  \\___ \\ / _ \\/ _ \\/ _` | |    | |/ _` / __/ __|
                  ____) |  __/  __/ (_| | |____| | (_| \\__ \\__ \\
                 |_____/ \\___|\\___|\\__,_|\\_____|_|\\__,_|___/___/

'''.format(__version__))


parser = ArgumentParser(
    formatter_class=RawDescriptionHelpFormatter,
    description='Binary classifier that extracts features from seed files and predicts their vulnerability potential.',
    prog='SeedClass'
)

parser.add_argument('-N', '--negative', dest='negative',
                    help='path to archive containing negative samples')
parser.add_argument('-P', '--positive', dest='positive',
                    help='path to archive containing positive samples')
parser.add_argument('-U', '--unknown', dest='unknown',
                    help='path to archive containing unknown samples')
parser.add_argument('-S', '--selected', dest='selected',
                    help='path to archive containing selected samples')

parser.add_argument('-E', '--encoding', dest='encoding', choices=['simple', 'product'], default='simple',
                    help='encoding method to use (simple or product)')
parser.add_argument('-V', '--validation', dest='validation', action='store_true',
                    help='whether or not use cross-validation (default false)')
parser.add_argument('-R', '--regularization', dest='regularization', action='store_true',
                    help='whether or not use L2 regularization (default false)')

parser.add_argument('--seed', dest='seed', type=int, default=None,
                    help='set initial seed (default none)')
parser.add_argument('--num-features', dest='num_features', type=int, default=256,
                    help='set number of features (default 256)')
parser.add_argument('--test-size', dest='test_size', type=float, default=0.25,
                    help='set test size (default 0.25)')
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

parser.add_argument('--save', dest='save', action='store_true',
                    help='save model and scaler to file')
parser.add_argument('--verbose', dest='verbose', action='store_true',
                    help='run in verbose mode')

args = parser.parse_args()


ENCODING          = args.encoding
VALIDATION        = args.validation
REGULARIZATION    = args.regularization

FEATURE_RANGE_MAX_SIMPLE = 0.646464646464
FEATURE_RANGE_MAX_PRODUCT = (pow(64, 6)) / pow(10, 11) # 0.68719476736

FEATURE_RANGE_MAX = FEATURE_RANGE_MAX_SIMPLE if ENCODING == 'simple' else FEATURE_RANGE_MAX_PRODUCT
NUM_FEATURES      = args.num_features         # Default is 256
TEST_SIZE         = args.test_size            # Default is 0.25
BATCH_SIZE        = args.batch_size           # Default is 32
LEARNING_RATE     = args.learning_rate        # Default is 0.001
SEED              = args.seed                 # Default is None
N_SPLITS          = args.nsplits              # Default is 4
EPOCHS            = args.epochs               # Default is 10
SAVE              = args.save                 # Default is 0
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


def load_data(data, archive, label=LABEL_NEGATIVE):
    def process(data):

        # Normalize decimal numbers.
        def scale(X):
            return [(i - min(X)) / (max(X) - min(X)) * FEATURE_RANGE_MAX for i in X]

        # Yield successive n-sized chunks from a list.
        def chunks(lst, n):
            return [lst[i:i + n] for i in range(0, len(lst), n)]

        # Encode file content via Base64 and map each byte using CHARMAP.
        encoded = [CHARMAP.get(chr(i), 0) for i in b64encode(data)]

        # Group every 6 numbers into a single decimal feature.
        decimal = [
            np.prod(np.array(chunk)[np.array(chunk) != 0]) if ENCODING == 'product'
            else int(''.join(map(str, chunk)))
            for chunk in chunks(encoded, 6)
        ]

        # Pad the feature list to NUM_FEATURES elements.
        while len(decimal) < NUM_FEATURES:
            decimal.append(0)
        return decimal

    good, bad = [], []
    try:
        logging.info('Processing archive {} containing samples for label {}'.format(archive, label))
        with open(archive, 'rb') as file:
            stream = io.BytesIO(file.read())
        with ZipFile(stream, 'r') as zip:
            for info in zip.infolist():
                if info.filename.lower().endswith('.emf'):
                    with zip.open(info.filename) as f:
                        features = process(f.read())
                        features[:0] = [label]
                        if len(features) == NUM_FEATURES+1: # Ignore too big files
                            good.append(len(features))
                            data.update({os.path.basename(info.filename): features})
                        else:
                            bad.append(len(features))
                            print('Ignoring {} which has {} features and is {} bytes'.format(os.path.basename(info.filename), len(features), info.file_size))
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


def build_model():
    model = Sequential()
    model.add(Input(shape=(NUM_FEATURES,)))
    model.add(Dense(NUM_FEATURES, activation='relu', kernel_regularizer=L2(0.00001) if REGULARIZATION else None))
    model.add(Dropout(0.5))
    model.add(Dense(NUM_FEATURES, activation='relu', kernel_regularizer=L2(0.00001) if REGULARIZATION else None))
    model.add(Dropout(0.5))
    model.add(Dense(1, activation='sigmoid'))

    model.compile(
        optimizer=Adam(learning_rate=LEARNING_RATE),
        loss='binary_crossentropy',
        metrics=[BinaryAccuracy(name='accuracy', threshold=THRESHOLD),
            Recall(thresholds=THRESHOLD, name='recall'),
            Precision(thresholds=THRESHOLD, name='precision'),
            TruePositives(thresholds=THRESHOLD, name='tp'),
            TrueNegatives(thresholds=THRESHOLD, name='tn'),
            FalsePositives(thresholds=THRESHOLD, name='fp'),
            FalseNegatives(thresholds=THRESHOLD, name='fn'),
            AUC(name='auc'),
            AUC(name='prc', curve='PR')
        ]
    )
    return model


def take_rows(data, indices):
    if hasattr(data, 'iloc'):
        return data.iloc[indices]
    return data[indices]


def train_model(X_train, y_train):
    final_epochs = EPOCHS

    if VALIDATION:
        best_epochs = []
        labels = np.asarray(y_train).reshape(-1)
        kfold = StratifiedKFold(n_splits=N_SPLITS, shuffle=True, random_state=SEED)
        for fold, (train, test) in enumerate(kfold.split(X_train, labels), start=1):
            fold_scaler = MinMaxScaler(feature_range=(0, FEATURE_RANGE_MAX))
            X_fold_train = fold_scaler.fit_transform(take_rows(X_train, train))
            X_fold_val = fold_scaler.transform(take_rows(X_train, test))
            y_fold_train = np.asarray(take_rows(y_train, train)).reshape(-1)
            y_fold_val = np.asarray(take_rows(y_train, test)).reshape(-1)

            model = build_model()
            history = model.fit(
                x=X_fold_train,
                y=y_fold_train,
                batch_size=BATCH_SIZE,
                epochs=EPOCHS,
                verbose=VERBOSE,
                validation_data=(X_fold_val, y_fold_val),
                callbacks=[
                    EarlyStopping(monitor='val_loss', mode='min', patience=5, restore_best_weights=True),
                ]
            )

            val_loss = np.asarray(history.history.get('val_loss', []), dtype=np.float64)
            if val_loss.size == 0:
                raise ValueError(f'Fold {fold}: no validation loss was recorded')
            if not np.all(np.isfinite(val_loss)):
                raise ValueError(f'Fold {fold}: validation loss contains non-finite values')

            best_epoch = int(np.argmin(val_loss)) + 1
            best_epochs.append(best_epoch)
            logging.info(f'Fold {fold}/{N_SPLITS}: best epoch {best_epoch} of {len(val_loss)} trained (val_loss {val_loss[best_epoch - 1]:.4f})')
            if len(val_loss) >= EPOCHS:
                logging.warning(f'Fold {fold}/{N_SPLITS}: exhausted the epoch cap ({EPOCHS}) without early stopping; epoch search is capped')

        mean_epochs = float(np.mean(best_epochs))
        final_epochs = max(1, int(np.ceil(mean_epochs)))
        logging.info(f'Best epochs per fold: {best_epochs} - Mean: {mean_epochs:.2f} - Chosen final epochs: {final_epochs}')
    else:
        logging.info(f'No epoch search; using configured {final_epochs} epochs for final training')

    final_scaler = MinMaxScaler(feature_range=(0, FEATURE_RANGE_MAX))
    X_final = final_scaler.fit_transform(X_train)
    y_final = np.asarray(y_train).reshape(-1)

    final_model = build_model()
    final_model.fit(
        x=X_final,
        y=y_final,
        batch_size=BATCH_SIZE,
        epochs=final_epochs,
        verbose=VERBOSE
    )

    return final_model, final_scaler


def main():
    if not os.path.isfile(args.negative):
        logging.error(f'Archive of negative samples {args.negative} does not exist or it is not a file!')
        sys.exit(1)

    if not os.path.isfile(args.positive):
        logging.error(f'Archive of positive samples {args.positive} does not exist or it is not a file!')
        sys.exit(1)

    if not os.path.isfile(args.unknown):
        logging.error(f'Archive of unknown samples {args.unknown} does not exist or it is not a file!')
        sys.exit(1)

    if VERBOSE:
        logging.info('Running in verbose mode')

    if ENCODING:
        logging.info(f'Using {ENCODING} encoding ({FEATURE_RANGE_MAX}) for feature scaling')

    if VALIDATION:
        logging.info(f'Using {N_SPLITS}-fold cross-validation for training')

    if REGULARIZATION:
        logging.info('Using L2 kernel regularization (0.00001) in Dense layers')

    if SEED is not None:
        tf.keras.utils.set_random_seed(SEED)

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
        shuffle=True,
        stratify=y)

    model, scaler = train_model(X_train, y_train)

    X_train = pd.DataFrame(scaler.transform(X_train)).values
    X_test = pd.DataFrame(scaler.transform(X_test)).values

    if SAVE:
        scale = scaler.scale_.astype(np.float64)
        min_  = scaler.min_.astype(np.float64)

        assert scale.shape == min_.shape
        assert scale.ndim == 1

        with open("scaler.bin", "wb") as f:
            np.array([len(scale)], dtype=np.int32).tofile(f)
            scale.tofile(f)
            min_.tofile(f)

    scores = model.evaluate(X_test, y_test, verbose=VERBOSE)
    logging.info(f'Loss: {scores[0] * 100:.2f}% - Recall: {scores[2] * 100:.2f}% - Precision: {scores[3] * 100:.2f}% - PRC: {scores[9] * 100:.2f}%')

    if SAVE:
        spec = [tf.TensorSpec([None, NUM_FEATURES], tf.float32, name="input")]

        @tf.function(input_signature=spec)
        def model_fn(x):
            return model(x, training=False)

        onnx_model, _ = tf2onnx.convert.from_function(model_fn, input_signature=spec, opset=18)
        onnx.checker.check_model(onnx_model)
        onnx.save(onnx_model, "model.onnx")

    dd = {}
    if args.unknown:
        dd = load_data(dd, args.unknown)

    df = pd.DataFrame.from_dict(dd, orient='index').add_prefix('f')

    raw_scores = []
    if len(df.index) > 0:
        X_pred = df.drop('f0', axis=1).values
        X_pred = pd.DataFrame(scaler.transform(X_pred))
        raw_scores = [score for row in model.predict(X_pred, verbose=VERBOSE) for score in row]

    if not np.all(np.isfinite(raw_scores)):
        raise ValueError('Prediction scores contain non-finite values')
    ranked = sorted(range(len(raw_scores)), key=lambda i: (-raw_scores[i], df.index[i]))
    above = [i for i in ranked if raw_scores[i] > THRESHOLD]
    indices = (above or ranked)[:20]
    lst = [df.index[i] for i in indices]

    logging.info(f'Selected {len(lst)} files out of {len(df.index)} total')

    try:
        for filename in lst:
            logging.info(filename)
            if args.selected:
                os.makedirs(args.selected, exist_ok=True)
                with ZipFile(args.unknown, 'r') as fzip:
                    selected = None
                    for name in fzip.namelist():
                        if name.endswith(f'{filename}'):
                            selected = name
                            break
                    if selected:
                        with fzip.open(selected) as fsrc:
                            dst = os.path.join(args.selected, filename)
                            with open(dst, 'wb') as fdst:
                                copyfileobj(fsrc, fdst)
    except:
        logging.error('Something, somewhere went terribly wrong!')
        pass


if __name__ == '__main__':
    main()
