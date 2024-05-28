import numpy as np

a = np.arange(10)
b = a[5]
c = a[2:7:2]       #从索引2开始到索引7结束，间隔为2
d = a[2:7]
e = a[2:]
print('============================')
print(a)
print(b)
print(c)
print(d)
print(e)
print('============================')

'''
============================
[0 1 2 3 4 5 6 7 8 9]
5
[2 4 6]
[2 3 4 5 6]
[2 3 4 5 6 7 8 9]
============================
'''