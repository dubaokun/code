#!/usr/bin/python
# -*- coding: UTF-8 -*-

class A(object):
    def __init__(self):
        self._a = 0

    def get(self):
        return self._a

    def set(self):
        self._a += 1

def TestA(max):
    n = 0;
    a = A()
    while n < max:
        yield a
        n += 1
 
def fab(max): 
    n, a, b = 0, 0, 1 
    while n < max: 
        yield b      # 使用 yield
        print b 
        #a, b = b, a + b 
        n = n + 1
 
for n in fab(5): 
    n = n + 1
    print n

print '====================='
for m in TestA(5):
    print m.get()
    m.set()
