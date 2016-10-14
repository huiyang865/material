#!/usr/bin/env python
# -*- coding: utf-8 -*-
# for use alone
import sys
import os
import codecs
import time
from collections import Counter
import logging
try:
    import tornado.log
    tornado.log.enable_pretty_logging()
except:
    pass
logging.basicConfig(level=logging.DEBUG)  # INFO

fname = sys.argv[1]
_n = sys.argv[2]

fname1 = fname + '_ng%s' % _n
f1 = open(fname1, 'w+')


def _counter(alist, n=None, min_count=None):
    if min_count:
        for i in Counter(alist).most_common(n):
            if i[1] < min_count:
                break
            yield i
    else:
        for i in Counter(alist).most_common(n):
            yield i


def gen_txt(fname, aencode='utf-8', errors='strict'):  # ignore
    fname = os.path.abspath(fname)
    if os.path.isfile(fname):
        with codecs.open(fname, 'r', 'utf-8', errors='ignore') as f:
            for word in f:
                # if str is not unicode_type:  # py2 # todo:py3 coverage
                #     word = word.decode(aencode, errors=errors)
                yield word.rstrip('\n')
    else:
        logging.warn('file %s not found' % fname)


def get_ngram(words, n=2, sep='_'):
    return [sep.join(words[i:i + n]) for i in range(len(words) - n + 1)]


def gen():
    res = gen_txt(fname)
    for i in res:
        sent = i.split()
        for j in get_ngram(sent, sep='', n=int(_n)):
            yield j

t_st = time.time()

for i in _counter(gen()):
    ret = '%s\t%s\n' % (i[1], i[0])
    f1.write(ret.encode('u8'))

f1.close()
logging.warn('time: %d s' % (time.time() - t_st))
