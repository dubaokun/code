#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
class Fab(object): 
 
    def __init__(self, max): 
        self.max = max 
        self.n, self.a, self.b = 0, 0, 1 
 
    def __iter__(self): 
        return self 
 
    def next(self): 
        if self.n < self.max: 
            r = self.b 
            self.a, self.b = self.b, self.a + self.b 
            self.n = self.n + 1 
            print 'aaaa'
            return r 
        raise StopIteration()
 
for n in Fab(5): 
    print n
