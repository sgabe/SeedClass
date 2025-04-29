# Copyright (c) 2025 Gabor Seljan. All rights reserved.
# Licensed under the MIT License.

import os

from datetime import datetime

ENCODING          = True
VALIDATION        = True
REGULARIZATION    = True

FEATURE_RANGE_MAX = 0.646464646464 if ENCODING else (pow(64, 6))/pow(10,11) # 0.68719476736
LOG_DIR           = os.path.join(os.getcwd(), 'logs/fit/' + datetime.now().strftime('%Y%m%d-%H%M%S'))
TEST_SIZE         = 0.25                      # Default is 0.25
BATCH_SIZE        = 32                        # Default is 32
LEARNING_RATE     = 0.001                     # Default is 0.001
SEED              = None                      # Default is None
N_SPLITS          = 4
EPOCHS            = 10
VERBOSE           = 0

# Increase for lower FP and higher precision yielding less files.
# Decrease for lower FN and higher recall yielding more files.
THRESHOLD         = 0.50                      # Default is 0.50

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
