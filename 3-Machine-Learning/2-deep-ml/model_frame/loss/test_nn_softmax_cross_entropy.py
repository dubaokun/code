import tensorflow as tf

labels_dense = [[0, 1, 0], [0, 1, 0], [1, 0, 0]]
labels_sparse = [1, 1, 0]

logits = tf.constant(value=[[0.3, 0.3, 0.2], [0, 1, 1.5], [1, 1, 0]],
    dtype=tf.float32, shape=[3, 3])

loss_dense = tf.losses.softmax_cross_entropy(onehot_labels=labels_dense, logits=logits)
loss_sparse =tf.losses.sparse_softmax_cross_entropy(labels=labels_sparse, logits=logits)

with tf.Session() as sess:
  print('===============================')
  print('logits:', sess.run(logits))
  print('tf.nn.softmax_cross_entropy:', sess.run(loss_dense))
  print('tf.nn.sparse_softmax_cross_entropy:', sess.run(loss_sparse))
  print('================================')
