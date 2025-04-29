# Copyright (c) 2025 Gabor Seljan. All rights reserved.
# Licensed under the MIT License.

import os
import config
import numpy as np
import pandas as pd
import tensorflow as tf
import matplotlib.pyplot as plt

from base64 import b64encode
from sklearn.metrics import precision_recall_curve

if config.SEED:
    np.random.seed(config.SEED)
    tf.random.set_seed(config.SEED)

np.set_printoptions(suppress=True)
np.set_printoptions(precision=16)
pd.set_option('display.precision', 16)


def load_data(data, dir, label=config.LABEL_NEGATIVE):
  def process(path):

    # Normalize decimal numbers
    def scale(X):
      lst = list()
      for i in X:
        lst.append((i-min(X))/(max(X)-min(X)) * config.FEATURE_RANGE_MAX)
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
        encoded.append(config.CHARMAP[chr(i)])

    # Group every 6 number to a larger decimal
    decimal = list()
    for i in chunks(encoded, 6):
        if config.ENCODING:
            decimal.append(int(''.join(map(str, i))))
        else:
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
    print('Processing directory {} containing samples for label {}'.format(os.path.join(os.getcwd(), dir), label))
    for file in [f for f in os.listdir(os.path.join(os.getcwd(), dir)) if f.lower().endswith('.emf')]:
      features = process(os.path.join(os.getcwd(), dir, file))
      features[:0] = [label]
      if len(features) == 257: # Ignore too big files
        good.append(len(features))
        data.update({file: features})
      else:
        bad.append(len(features))
        print('Ignoring {} which has {} features and is {} bytes'.format(file, len(features), os.path.getsize(os.path.join(os.getcwd(), dir, file))))
  except FileNotFoundError:
    print('The system cannot find the path specified!')
  except Exception as e:
    print('Something, somewhere went terribly wrong!')
    pass
  finally:
    print(f'Good: {len(good)} - Bad: {len(bad)} - Ratio: {len(bad)/(len(bad)+len(good)) * 100:.2f}%')
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


def plot_prc(name, labels, predictions, **kwargs):
    precision, recall, _ = precision_recall_curve(labels, predictions)
    plt.plot(precision, recall, label=name, linewidth=2, **kwargs)
    plt.xlabel('Precision')
    plt.ylabel('Recall')
    plt.grid(True)
    ax = plt.gca()
    ax.set_aspect('equal')
    plt.legend(loc='lower right');


def plot_cross_val_essential_metrics(metrics, histories):
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


def plot_cross_val_confusion_metrics(metrics, histories):
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
