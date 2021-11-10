import tensorflow.compat.v1 as tf

tf.disable_v2_behavior()

sp = tf.SparseTensor(indices=[[0,2],[1,3]], values=[1,2], dense_shape=[3,4])
with tf.Session() as tf:
    print(sp.eval())
