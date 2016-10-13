# -*- coding: utf-8 -*-

import csv
import re

csvfile = file(r'e:\fail_shuyushi.csv', 'rb')
reader = csv.reader(csvfile)
result_csv = []

def get_wuxian_jisuan():
    for line in reader:
        line_content = line[0]
        print line_content
        result = re.match('.*计算.*…', line_content)
        if result is not None:
            id = line_content.split('\t')[0]
            result_csv.append(id)
            result_csv.append('\n')

def write_csv_content():
    resultfile = file(r'e:\wuxian_jisuan.txt', 'a')
    for item in result_csv:
        resultfile.write(item)

if __name__ == '__main__':
    get_wuxian_jisuan()
    write_csv_content()
