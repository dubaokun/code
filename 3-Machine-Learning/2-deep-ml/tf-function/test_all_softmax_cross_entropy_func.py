import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()

labels_sparse = [1, 1, 0]
labels_onehot = [[0, 1, 0], [0, 1, 0], [1, 0, 0]]

logits = tf.constant(value=[[0.3, 0.3, 0.2], [0, 1, 0.5], [1, 1, 0]], dtype=tf.float32, shape=[3, 3])


loss = tf.nn.softmax_cross_entropy_with_logits_v2(labels=labels_onehot, logits=logits)
loss = tf.reduce_mean(loss)
loss_sparse = tf.nn.sparse_softmax_cross_entropy_with_logits(labels=labels_sparse, logits=logits)
loss_sparse = tf.reduce_mean(loss_sparse)

loss2=tf.losses.softmax_cross_entropy(onehot_labels=labels_onehot, logits=logits)
loss_sparse2 = tf.losses.sparse_softmax_cross_entropy(labels=labels_sparse,
        logits=logits)

with tf.Session() as sess:
  print('logits:', sess.run(logits))
  print('tf.nn.softmax_cross_entropy_with_logits_v2:', sess.run(loss))
  print('tf.nn.sparse_softmax_cross_entropy_with_logits:', sess.run(loss_sparse))
  print('tf.losses.softmax_cross_entropy:', sess.run(loss2))
  print('tf.losses.sparse_softmax_cross_entropy:', sess.run(loss_sparse2))
