import tensorflow as tf
import numpy as np
 
inputs = tf.constant(np.arange(1, 6, dtype=np.float32), shape=[1, 5, 1])
w = np.array([1, 2], dtype=np.float32).reshape([2, 1, 1])
# filter width, filter channels and out channels(number of kernels)
cov1 = tf.nn.conv1d(inputs, w, stride=1, padding='VALID')

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    out = sess.run(cov1)
    print(out)
