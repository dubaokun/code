import numpy as np
import scipy.sparse as sp

A=np.array([[1,0,2,0],[0,0,0,0],[3,0,0,0],[1,0,0,4]])
AS=sp.lil_matrix(A)

print(AS.data)
# [list([1, 2]) list([]) list([3]) list([1, 4])]
print(AS.rows)
# [list([0, 2]) list([]) list([0]) list([0, 3])]
print('===========================')
print(AS)
print('===========================')
print(AS.shape)
print('===========================')
print(type(AS))

