import tensorflow as tf

# 设计Graph
x1 = tf.placeholder(tf.int16)
x2 = tf.placeholder(tf.int16)
y = tf.add(x1, x2)
# 产生数据
li1 = [1, 2, 3]
li2 = [4, 5, 6]

with tf.Session() as sess:
    print('===========================')
    print(sess.run(y, feed_dict={x1: li1, x2: li2}))
    print('===========================')
