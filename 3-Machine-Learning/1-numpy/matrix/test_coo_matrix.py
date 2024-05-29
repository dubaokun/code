# 坐标格式的矩阵(Coodrdinate format matrix)
"""
优点：
  1.不同稀疏格式间转换效率高(exp:CSR/CSC)
  2.coo_matrix不支持元素的存取和增删，一旦创建之后，除了将之转换成其它格式的矩阵，几乎无法对其做任何操作和矩阵运算。
  3.构建矩阵时，允许坐标重复
缺点：
  1.不能直接运算
  2.不能直接切片操作
"""
import scipy.sparse as sp
data = [1, 1, 1]
row = [0, 1, 1]
col = [0, 1, 1]
matrix = sp.coo_matrix((data, (row, col)), shape=(3, 3))
#matrix.todense()
print("================")
print(matrix)
print("================")
print(matrix.todense())

