import numpy as np

a = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
print('=========================')
print(a.shape)
print(a)
print('=========================')
print(a[1,1])
print('=========================')
print('a[1:]=')
print(a[1:])
print('=========================')
print('a[:,1]=')
print(a[:,1])
print('=========================')
print(a[...,1])
print('=========================')
print(a[:,1:])
print('=========================')

'''
=========================
(3, 3)
[[1 2 3]
 [4 5 6]
 [7 8 9]]
=========================
5
=========================
a[1:]=
[[4 5 6]
 [7 8 9]]
=========================
a[:,1]=
[2 5 8]
=========================
[2 5 8]
=========================
[[2 3]
 [5 6]
 [8 9]]
=========================
'''