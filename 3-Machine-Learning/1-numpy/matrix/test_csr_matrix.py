"""
csr_matrix: 压缩稀疏行矩阵(Compressed sparse row matrix)
优点：

高效的矩阵加法与乘法内积运算
高效的行切片操作
CSR格式在存储稀疏矩阵时非零元素平均使用的字节数(Bytes per Nonzero
Entry)最为稳定（float类型约为8.5，double类型约为12.5）CSR格式常用于读入数据后进行稀疏矩阵计算。
缺点：

列切片操作慢（相比CSC)
转换成稀疏结构成本高（相比LIL)

https://www.cnblogs.com/jzYe/p/17806891.html

"""
import scipy.sparse as sp
import numpy as np
indptr = np.array([0, 2, 3, 6])
indices = np.array([0, 2, 2, 0, 1, 2])
data = np.array([1, 2, 3, 4, 5, 6])
matrix = sp.csr_matrix((data, indices, indptr), shape=(3, 3))
matrix.todense()
print('=============')
print(matrix.shape)
print('=============')
print(matrix)
print('=============')
print(matrix[0])
print(matrix[0].shape)
print('=============')
print(matrix[0][0])
print(matrix[0][0].shape)
print('=============')
print(matrix.todense())
