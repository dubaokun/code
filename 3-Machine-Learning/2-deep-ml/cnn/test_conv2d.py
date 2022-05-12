# coding: utf-8
import tensorflow as tf
 
 # 定义输入图像size
 img_size = 256
 # 卷积核大小
 kernel_size = 7
 # 卷积步长
 stride_size = 1
  
# 读入图像文件
image_value = tf.read_file('./661.jpg')
# 图像编码
img = tf.image.decode_jpeg(image_value, channels=3)
# 格式转换
img = tf.to_float(img, name='ToFloat')
# 调整图像大小到定义尺寸
img = tf.image.resize_images(img, [img_size,img_size],method=0)
   
# 第一个参数1是输入图片数量，最后一个3个RGB3个维度
batch_shape = (1,img_size,img_size,3)
# 维度转换，为卷积做准备（卷积的输入特征图的rank必须是4)
img = tf.reshape(img,batch_shape)
    
# 卷积核大小5×5,深度是3（跟RGB3个维度保持一致），特征图（卷积核）数量是7
filter = tf.Variable(tf.random_normal([kernel_size,kernel_size,3,7]))
# 步长1
strides_shape=[1,stride_size,stride_size,1]
# 定义卷积操作
op_conv2d = tf.nn.conv2d(img, filter, strides_shape, padding='SAME')
     
# 创建运行sess
with tf.Session() as sess:
  sess.run(tf.global_variables_initializer())
  out_img= sess.run(op_conv2d)
  print('输入图像维度： {}'.format(img.shape))
  print('输出图像维度： {}'.format(out_img.shape))
  # 输入图像维度： (1, 256, 256, 3)
  # 输出特征图维度： (1, 256, 256, 7)
