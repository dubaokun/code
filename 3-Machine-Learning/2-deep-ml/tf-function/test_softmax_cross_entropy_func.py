import tensorflow as tf

# our NN's output
logits=tf.constant([[1.0,2.0,3.0],[1.0,2.0,3.0],[1.0,2.0,3.0]])
#true label
y_=tf.constant([[0.0,0.0,1.0],[0.0,0.0,1.0],[0.0,0.0,1.0]])

# function: tf.nn.softmax_cross_entropy_with_logits
cross_entropy1=tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y_,
    logits=logits))                                     # dont forget tf.reduce_sum()!!
# function: tf.losses.softmax_cross_entropy
cross_entropy2=tf.losses.softmax_cross_entropy(onehot_labels=y_, logits=logits)
  
with tf.Session() as sess:
  c_e1 = sess.run(cross_entropy1)
  c_e2 = sess.run(cross_entropy2)
  print("Function(softmax_cross_entropy_with_logits) result=")
  print(c_e1)
  print("Function(softmax_cross_entropy) result=")
  print(c_e2)
