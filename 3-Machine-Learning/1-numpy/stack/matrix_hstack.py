import numpy as np

a = np.array([[1, 2], [3, 4]])
b = np.array([[5, 6], [7, 8]])
# 水平组合
c = np.hstack((a, b))
print('==========================')
print(c.shape)
print(c)
print('==========================')
d = np.concatenate((a, b), axis=1)
print(d.shape)
print(d)
