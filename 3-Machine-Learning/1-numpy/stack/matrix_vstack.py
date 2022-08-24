import numpy as np

a = np.array([[1, 2], [3, 4]])
b = np.array([[5, 6], [7, 8]])

# 垂直组合，垂直拼接
c = np.vstack((a, b))
print('==========================')
print(c.shape)
print(c)
print('==========================')
d = np.concatenate((a, b), axis=0)
print(d.shape)
print(d)
