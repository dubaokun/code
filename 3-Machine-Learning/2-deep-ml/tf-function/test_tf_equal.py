import tensorflow as tf
a = [[1,2,3],[4,5,6]]
b = [[1,0,3],[1,5,1]]
with tf.Session() as sess:
    print(sess.run(tf.equal(a,b)))
