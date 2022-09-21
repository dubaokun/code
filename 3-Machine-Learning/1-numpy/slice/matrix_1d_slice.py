import numpy as np

a = np.arange(10)
b = a[5]
c = a[2:7:2]       #从索引2开始到索引5结束，间隔为2
d = a[2:7]
e = a[2:]
print('============================')
print(a)
print(b)
print(c)
print(d)
print(e)
print('============================')
