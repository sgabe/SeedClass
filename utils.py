# Copyright (c) 2025 Gabor Seljan. All rights reserved.
# Licensed under the MIT License.

import io
import os
import config
import numpy as np
import pandas as pd
import tensorflow as tf
import matplotlib.pyplot as plt

from zipfile import ZipFile
from base64 import b64encode
from sklearn.metrics import precision_recall_curve

if config.SEED:
    np.random.seed(config.SEED)
    tf.random.set_seed(config.SEED)

np.set_printoptions(suppress=True)
np.set_printoptions(precision=16)
pd.set_option('display.precision', 16)


def load_data(data, archive, label=config.LABEL_NEGATIVE):
    def process(data):
        # Normalize decimal numbers.
        def scale(X):
            return [(i - min(X)) / (max(X) - min(X)) * config.FEATURE_RANGE_MAX for i in X]

        # Yield successive n-sized chunks from a list.
        def chunks(lst, n):
            return [lst[i:i + n] for i in range(0, len(lst), n)]

        # Encode file content via Base64 and map each byte using CHARMAP.
        encoded = [config.CHARMAP.get(chr(i), 0) for i in b64encode(data)]

        # Group every 6 numbers into a single decimal feature.
        decimal = [
            np.prod(np.array(chunk)[np.array(chunk) != 0]) if config.ENCODING == 'product'
            else int(''.join(map(str, chunk)))
            for chunk in chunks(encoded, 6)
        ]

        # Pad the feature list to 256 elements.
        while len(decimal) < 256:
            decimal.append(0)
        return decimal

    good, bad = [], []
    try:
        print('Processing archive {} containing samples for label {}'.format(archive, label))
        with open(archive, 'rb') as file:
            stream = io.BytesIO(file.read())
        with ZipFile(stream, 'r') as zip:
            for info in zip.infolist():
                if info.filename.lower().endswith('.emf'):
                    with zip.open(info.filename) as f:
                        features = process(f.read())
                        features[:0] = [label]
                        if len(features) == 257: # Ignore too big files
                            good.append(len(features))
                            data.update({os.path.basename(info.filename): features})
                        else:
                            bad.append(len(features))
                            print('Ignoring {} which has {} features and is {} bytes'.format(os.path.basename(info.filename), len(features), info.file_size))
    except FileNotFoundError:
        print('The system cannot find the path specified!')
    except Exception as e:
        print('Something, somewhere went terribly wrong!')
        pass
    finally:
        total = len(good) + len(bad)
        ratio = (len(bad) / total * 100) if total > 0 else 0
        print(f'Good: {len(good)} - Bad: {len(bad)} - Ratio: {ratio:.2f}%')
        return data


def plot_essential_metrics(metrics, history):
    for n, metric in enumerate(metrics):
        name = metric.replace("_"," ").capitalize()
        plt.subplot(2,2,n+1)
        plt.plot(history.epoch, history.history[metric], color='C{}'.format(n), label='Train')
        plt.plot(history.epoch, history.history['val_'+metric], color='C{}'.format(n), linestyle="--", label='Val')
        plt.xlabel('Epoch')
        plt.ylabel(name)
        plt.suptitle('Essential Metrics')

        if metric == 'loss':
            plt.ylim([0,0.6])
        elif metric == 'auc':
            plt.ylim([0.7,1])
        elif metric == 'prc':
            plt.ylim([0.9,1])
        elif metric == 'precision':
            plt.ylim([0.9,1])
        else:
            plt.ylim([0.7,1])

        ax = plt.gca()
        plt.legend()
        plt.tight_layout()
    plt.show()


def plot_confusion_metrics(metrics, history):
    fig = plt.figure()
    for n, metric in enumerate(metrics):
        name = metric.replace("_"," ").capitalize()
        for i, phase in enumerate(['Training', 'Validation']):
            plt.subplot(1, 2, i + 1)
            if phase == 'Validation':
                plt.plot(history.epoch, history.history['val_'+metric], color='C{}'.format(n), linestyle='--', label=name)
            else:
                plt.plot(history.epoch, history.history[metric], color='C{}'.format(n), label=name)
            plt.xlabel('Epoch')
            plt.ylabel('Sample')
            plt.title(f'{phase} Metrics')
            plt.legend()
    plt.tight_layout()
    plt.show()
    fig.savefig(os.path.join('figures', 'learning', 'metrics-confusion.png'), bbox_inches='tight')


def plot_prc(name, labels, predictions, **kwargs):
    precision, recall, _ = precision_recall_curve(labels, predictions)
    plt.plot(precision, recall, label=name, linewidth=2, **kwargs)
    plt.xlabel('Precision')
    plt.ylabel('Recall')
    plt.grid(True)
    ax = plt.gca()
    ax.set_aspect('equal')
    plt.legend(loc='lower left');


def plot_cross_val_essential_metrics(metrics, histories):
    fig = plt.figure()
    for n, metric in enumerate(metrics):
        train_scores = []
        val_scores = []

        name = metric.replace("_"," ").capitalize()
        plt.subplot(2,2,n+1)

        for history in histories:
            for train_score in history.history[metric]:
                train_scores.append(train_score)

            for val_score in history.history['val_'+metric]:
                val_scores.append(val_score)

        plt.plot(train_scores, color='C{}'.format(n), label='Train')
        plt.plot(val_scores, color='C{}'.format(n), linestyle="--", label='Val')
        plt.ylabel(name)
        plt.legend()
        plt.tight_layout()
        plt.xlabel('Epoch')

        if metric == 'loss':
            plt.ylim([0,0.6])
        elif metric == 'auc':
            plt.ylim([0.7,1])
        elif metric == 'prc':
            plt.ylim([0.9,1])
        elif metric == 'precision':
            plt.ylim([0.9,1])
        else:
            plt.ylim([0.7,1])

        plt.suptitle('Essential Metrics')
    plt.show()
    fig.savefig(os.path.join('figures', 'learning', 'metrics-cross-val-essential.png'), bbox_inches='tight')


def plot_cross_val_confusion_metrics(metrics, histories):
    fig = plt.figure()
    for n, metric in enumerate(metrics):
        train_scores = []
        val_scores = []

        name = metric.replace("_"," ").capitalize()

        for history in histories:
            for train_score in history.history[metric]:
                train_scores.append(train_score)
            for val_score in history.history['val_'+metric]:
                val_scores.append(val_score)

        plt.plot(val_scores, color='C{}'.format(n), linestyle='--', label=name)
        plt.plot(train_scores, color='C{}'.format(n), label=name)
    plt.xlabel('Epoch')
    plt.ylabel('Sample')
    plt.title('Confusion Metrics')
    plt.legend()
    plt.tight_layout()
    plt.show()
    fig.savefig(os.path.join('figures', 'learning', 'metrics-cross-val-confusion.png'), bbox_inches='tight')
