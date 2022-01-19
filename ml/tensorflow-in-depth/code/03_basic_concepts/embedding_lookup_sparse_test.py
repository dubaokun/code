import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()

params = tf.constant([[0.1, 0.4, 0.7, 1.0, 1.3, 1.6, 1.9, 2.2, 2.5, 2.8],
                      [0.2, 0.5, 0.8, 1.1, 1.4, 1.7, 2.0, 2.3, 2.6, 2.9],
                      [0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.4, 2.7, 3.0]])

ids = tf.SparseTensor(indices=[[0, 1],
                               [0, 3],
                               [1, 2],
                               [1, 3]],
                      values=[2, 1, 1, 1],
                      dense_shape=[2, 4])

with tf.Session() as sess:
    lookup = sess.run(
        tf.nn.embedding_lookup_sparse(params, ids, None,
                                      partition_strategy="mod"))
print('*********************************************************************')
print(lookup)
