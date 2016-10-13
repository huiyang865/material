#!/usr/bin/env python
# coding:utf-8
"""
  Author:  Yang Hui --<hui.yang@wenba100.com>
  Purpose: 预处理文本信息
  Created: 2016/10/12  14:26
"""

import jieba
import jieba.analyse
import re
from read_write_data import *
zhPattern = re.compile(u'[\u4e00-\u9fa5]+')

def is_chinese(contents):
    """判断一个unicode是否是汉字"""
    if zhPattern.search(contents):
        return True
    else:
        return False

def cat_sentence4keys(all_text):
    """
    提取关键词
    :param text:
    :return:
    """
    key_results = []
    for item_text in all_text:
        tags = jieba.analyse.extract_tags(item_text, topK=100)
        tags_filter = [x for x in tags if is_chinese(x)]
        key_results.append(' '.join(tags_filter))
    return key_results

if __name__ == '__main__':
    all_text = read_math_data('../zzz_math_todo_part')
    key_results = cat_sentence4keys(all_text)
    write_data(key_results, '../LDA/data/train.dat')
