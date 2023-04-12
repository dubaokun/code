import numpy as np

a = np.array([[[1, 2, 3], [4, 5, 6], [7, 8, 9]], [[2, 2, 2], [3, 3, 3], [4, 4,
    4]], [[5, 5, 5], [6, 6, 6], [7, 7, 7]]])
print('=========================')
print(a.shape)
print(a)
print('=========================')
print('a[1:]=')
print(a[1:].shape)
print(a[1:])
print('=========================')
print('a[:,1]=')
print(a[:,1].shape)
print(a[:,1])
print('----------')
print('a[...,1]=')
print(a[...,1].shape)
print(a[...,1])
print('----------')
print(a[:,1:].shape)
print(a[:,1:])

'''

(3, 3, 3)
[[[1 2 3]
  [4 5 6]
  [7 8 9]]

 [[2 2 2]
  [3 3 3]
  [4 4 4]]

 [[5 5 5]
  [6 6 6]
  [7 7 7]]]
=========================
a[1:]=
(2, 3, 3)
[[[2 2 2]
  [3 3 3]
  [4 4 4]]

 [[5 5 5]
  [6 6 6]
  [7 7 7]]]
=========================
a[:,1]=
(3, 3)
[[4 5 6]
 [3 3 3]
 [6 6 6]]
----------
a[...,1]=
(3, 3)
[[2 5 8]
 [2 3 4]
 [5 6 7]]
----------
(3, 2, 3)
[[[4 5 6]
  [7 8 9]]

 [[3 3 3]
  [4 4 4]]

 [[6 6 6]
  [7 7 7]]]
'''