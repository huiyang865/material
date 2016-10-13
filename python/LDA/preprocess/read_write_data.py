#!/usr/bin/env python
# coding:utf-8
"""
  Author:  Yang Hui --<hui.yang@wenba100.com>
  Purpose: 获取zzz_math80todo文件中的内容
  Created: 2016/10/12  14:26
"""

import sys
reload(sys)
sys.setdefaultencoding( "utf-8" )

def read_math_data(path):
    """
    读取path路径中文件的内容
    :param path: 文件路径
    :return:
    """
    file_open = open(path)
    try:
        all_text = file_open.readlines()
    finally:
        file_open.close()
    return all_text

def write_data(all_text, path):
    """
    写入数据
    :param all_text: 数据内容
    :param path: 文件路径
    :return:
    """
    file_open = open(path, 'w+')
    try:
        for item_text in all_text:
            file_open.write(str(item_text)+'\n')
    finally:
        file_open.close()
