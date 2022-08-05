import tensorflow as tf

x = tf.constant([[1., 1.], [2., 2.]])
y = tf.constant([[[1,1,1], [2,2,2]],[[3,3,3],[4,4,4]],[[5,5,5],[6,6,6]]], dtype
        =tf.float64)
a = tf.reduce_mean(x)  # 1.5
b = tf.reduce_mean(x, 0)  # [1.5, 1.5]
c = tf.reduce_mean(x, 1)  # [1.,  2.]

# Part Y
a_1 = tf.reduce_mean(y, 1)
with tf.Session() as sess:
    print('=================================')
    print('x.shape=', x.shape)
    print(sess.run(a))
    print(sess.run(b))
    print(sess.run(c))
    print('=================================')
    print('=================================')
    print('y.shape=',y.shape)
    print('a_1.shape', a_1.shape)
    print(sess.run(a_1))
    print('=================================')