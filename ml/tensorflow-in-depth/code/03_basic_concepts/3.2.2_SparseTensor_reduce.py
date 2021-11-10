import tensorflow.compat.v1 as tf

tf.disable_v2_behavior()

sp = tf.SparseTensor(indices=[[0,0],[0,2],[1,0]], values=[1,1,1], dense_shape=[2,3])
reduce_sum_sp = [tf.sparse_reduce_sum(sp),
                tf.sparse_reduce_sum(sp, axis=1),
                tf.sparse_reduce_sum(sp, axis=1, keep_dims=True),
                tf.sparse_reduce_sum(sp, axis=0),
                tf.sparse_reduce_sum(sp, axis=0, keep_dims=True)
                ]
with tf.Session() as sess:
    print(sess.run(reduce_sum_sp))

