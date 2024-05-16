import tensorflow as tf
import numpy as np

NUM_ONEHOT_HASH, EMBEDDING_SIZE = 5, 6
y = tf.placeholder(name='class_idx', shape=(1,), dtype=tf.int32)

rs = np.random.RandomState(9)
em_weight_init = rs.randn(NUM_ONEHOT_HASH, EMBEDDING_SIZE)
em_weight = tf.get_variable(name='em_weight',
        initializer=tf.constant_initializer(em_weight_init), 
        shape=(NUM_ONEHOT_HASH, EMBEDDING_SIZE))

# using tf.nn.embedding_lookup
y_em_1 = tf.nn.embedding_lookup(em_weight, y)

# using tf.matmul
y_one_hot = tf.one_hot(y, depth=NUM_ONEHOT_HASH)
y_em_2 = tf.matmul(y_one_hot, em_weight)

sess = tf.InteractiveSession()
sess.run(tf.global_variables_initializer())
print(sess.run([y_em_1, y_em_2], feed_dict={y: [4.0]}))
