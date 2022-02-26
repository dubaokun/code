import tensorflow as tf

x = tf.constant([[1., 1.], [2., 2.]])
a = tf.reduce_mean(x)  # 1.5
b = tf.reduce_mean(x, 0)  # [1.5, 1.5]
c = tf.reduce_mean(x, 1)  # [1.,  2.]
with tf.Session() as sess:
    print(sess.run(a))
    print(sess.run(b))
    print(sess.run(c))
