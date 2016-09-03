# coding:utf-8
"""
    Author:  Yang Hui --<huiyang865@hotmail.com>
    Purpose: 插入排序
"""

def insertion_sort(array_temp):
    for i in range(2,len(array_temp)):
        key = array_temp[i]
        j = i - 1
        while j > 0 and array_temp[j] > key:
            array_temp[j + 1] = array_temp[j]
            j = j - 1
        array_temp[j] = key
    return array_temp

if __name__ == '__main__':
    print insertion_sort([2,1,33,52,3,67,23])
