#coding=utf-8
# 类似c++11的偏特化

import functools

def add(a, b):
    print(a + b)

add = functools.partial(add, 1)
add(2)
