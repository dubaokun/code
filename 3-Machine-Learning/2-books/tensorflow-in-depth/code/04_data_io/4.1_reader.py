# -*- coding: utf-8 -*-
import tensorflow as tf
# import tensorflow.compat.v1 as tf
 
# tf.disable_v2_behavior()
# 创建文件名队列filename_queue
filename_queue = tf.train.string_input_producer(['stat.tfrecord'], shuffle=True,
        num_epochs=2)
# 创建读取TFRecords文件的reader
reader = tf.TFRecordReader()
# 取出stat.tfrecord文件中的一条序列化的样例serialized_example
_, serialized_example = reader.read(filename_queue)
# 将一条序列化的样例转换为其包含的所有特征张量
features = tf.parse_single_example(
        serialized_example,
        features={
            'id': tf.FixedLenFeature([], tf.int64),
            'age': tf.FixedLenFeature([], tf.int64),
            'income': tf.FixedLenFeature([], tf.float32),
            'outgo': tf.FixedLenFeature([], tf.float32),
        }
)

# init_op = tf.global_variables_initializer()
init_op = tf.group(tf.global_variables_initializer(),
        tf.local_variables_initializer())
with tf.Session() as sess:
  sess.run(init_op)
  # 线程管理调度框架
  coord = tf.train.Coordinator()
  # 必须添加，否则不会触发框架进行样例的读取进入队列
  threads = tf.train.start_queue_runners(sess=sess, coord=coord)
  #tf.train.start_queue_runners(sess=sess)
  # print("Thread=%s" % threads)
  for i in range(2):
    example = sess.run(features);
    print(example)
  coord.join(threads)
