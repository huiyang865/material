# coding:utf-8
"""
    Author:  Yang Hui --<huiyang865@hotmail.com>
    Purpose: 插入排序
"""

def insertion_sort(array_temp):
    """
    插入排序
    :param array_temp: 输入数据(需要排序的数组)
    :return: 已排序后的数组
    """
    for i in range(1,len(array_temp)):
        key = array_temp[i]
        j = i - 1
        while j >= 0 and array_temp[j] > key:
            array_temp[j + 1] = array_temp[j]
            j = j - 1
        array_temp[j + 1] = key
        print array_temp
    return array_temp

if __name__ == '__main__':
    print insertion_sort([20,1,9,33,6,52,3,67,23])
