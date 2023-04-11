'''
tf.argmax(vector, 1)：返回的是vector中的最大值的索引号.
  1. 如果vector是一个向量，那就返回一个值，
  2. 如果是一个矩阵，那就返回一个向量，这个向量的每一个维度都是相对应矩阵行的最大值元素的索引号。
'''

import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()

import numpy as np
 
A = [[1,3,4,5,6]]
B = [[1,3,4], [2,4,1]]
C = [1,3,4,5,6]
  
with tf.Session() as sess:
  print(sess.run(tf.argmax(A, 1)))
  print(sess.run(tf.argmax(B, 1)))
  print("--------------------")
  print(sess.run(tf.argmax(A)))
  print(sess.run(tf.argmax(B)))
  print("--------------------")
  print(sess.run(tf.argmax(A, 0)))
  print(sess.run(tf.argmax(B, 0)))


# [4]
# [2 1]
# --------------------
# [0 0 0 0 0]
# [1 1 0]
# --------------------
# [0 0 0 0 0]
# [1 1 0]