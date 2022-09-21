import tensorflow as tf

# our NN's output
logits=tf.constant([[1.0,2.0,3.0],[1.0,2.0,3.0],[1.0,2.0,3.0]])

#step1:do softmax
y=tf.nn.softmax(logits)

#true label
y_=tf.constant([[0.0,0.0,1.0],[0.0,0.0,1.0],[0.0,0.0,1.0]])

tmp = y_*tf.log(y);

#step2:do cross_entropy
cross_entropy = -tf.reduce_sum(y_*tf.log(y))

#do cross_entropy just one step
cross_entropy2=tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y_,
    logits=logits)) #dont forget tf.reduce_sum()!!

cross_entropy3=tf.losses.softmax_cross_entropy(onehot_labels=y_, logits=logits)
  
with tf.Session() as sess:
  softmax=sess.run(y)
  tmp1 = sess.run(tmp)
  c_e = sess.run(cross_entropy)
  c_e2 = sess.run(cross_entropy2)
  c_e3 = sess.run(cross_entropy3)
  print("Step1:softmax result=")
  print(softmax)
  print('=====================')
  print(tmp1)
  print("step2:cross_entropy result=")
  print(c_e)
  print("Function(softmax_cross_entropy_with_logits) result=")
  print(c_e2)
  print("Function(softmax_cross_entropy) result=")
  print(c_e3)
