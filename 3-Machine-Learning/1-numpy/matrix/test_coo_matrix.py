import scipy.sparse as sp
data = [1, 1, 2]
row = [0, 1, 1]
col = [0, 1, 2]
matrix = sp.coo_matrix((data, (row, col)), shape=(3, 3))
#matrix.todense()
print("================")
print(matrix)
print("================")
print(matrix.todense())

