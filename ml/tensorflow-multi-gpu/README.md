



# 简介

TF的部署分为单机部署和分布式部署。在训练集数据量很大的情况下，单机跑深度学习程序过于耗时，所以需要分布式并行计算。在分布式部署中，我们需要在不同主机节点，实现client，master，worker。



# 背景 & 术语

- **ps devices**: 参数服务器，用于不同worker之间的同步，一般采用cpu
- **worker devices**:
- **Moving Average**: 这是参数的average，还是梯度的average？
  - 测评时，多次参数的均值通常会比单次模型参数效果要更好。
  - 多GPU并行时，不通的GPU会产生不同的模型参数，以及梯度。因此需要利用梯度平均（或者叫参数平均）
- **Exponential Moving Averaged**: 额外采用了指数衰减。shadow_variable = decay * shadow_variable + (1 - decay) * variable。`GradientDescent` 和 `Momentum` 方式的训练 都能够从 `ExponentialMovingAverage` 方法中获益。
- **multi-tower fashion**:


# 并行策略


通常的并行策略：。。。


TensorFlow的并行采用的是模型并行，数据并行。模型并行根据不同模型设计不同并行方式，模型不同计算节点放在不同硬伯上资源运算。数据并行，比较通用简便实现大规模并行方式，同时使用多个硬件资源计算不同batch数据梯度，汇总梯度全局参数更新。

- 数据并行，多块GPU同时训练多个batch数据，运行在每块GPU模型基于同一神经网络，网络结构一样，共享模型参数。
- 同步数据并行，所有GPU计算完batch数据梯度，统计将多个梯度合在一起，更新共享模型参数，类似使用较大batch。GPU型号、速度一致时，效率最高。
- 异步数据并行，不等待所有GPU完成一次训练，哪个GPU完成训练，立即将梯度更新到共享模型参数。
同步数据并行，比异步收敛速度更快，模型精度更高。


同步数据并行，数据集CIFAR-10。载入依赖库，TensorFlow Models cifar10类，下载CIFAR-10数据预处理。


## average_gradients



# tf多gpu，基本操作



如果你想让 TensorFlow 在多个 GPU 上运行, 你可以建立 multi-tower 结构, 在这个结构 里每个 tower 分别被指配给不同的 GPU 运行. 比如:


TensorFlow 支持 CPU 和 GPU 这两种设备，标识设备的方法为:

- "/cpu:0": 机器中的 CPU
- "/gpu:0": 机器中的 GPU, 如果你有一个的话.
- "/gpu:1": 机器中的第二个 GPU, 以此类推...


## 设备指派

```yml
#tf.ConfigProto()的参数
log_device_placement=True :  记录(打印)设备指派情况
allow_soft_placement=True :  如果你指定的设备不存在，允许TF自动分配设备
allow_growth=True : 刚一开始分配少量的GPU容量，然后按需慢慢的增加，由于不会释放内存，所以会导致碎片
```

控制使用哪块GPU

```sh
CUDA_VISIBLE_DEVICES=0
CUDA_VISIBLE_DEVICES=0,1
```
或者在python程序设置
```py
os.environ['CUDA_VISIBLE_DEVICES'] = '0' #使用 GPU 0
os.environ['CUDA_VISIBLE_DEVICES'] = '0,1' # 使用 GPU 0，1
```


## 记录设备指派情况

为了获取你的 operations 和 Tensor 被指派到哪个设备上运行, 用 log_device_placement 新建一个 session, 并设置为 True.

```py
# 新建一个 graph.
c = []
# 手工指派设备
for d in ['/device:GPU:2', '/device:GPU:3']:
  with tf.device(d):
    a = tf.constant([1.0, 2.0, 3.0, 4.0, 5.0, 6.0], shape=[2, 3])
    b = tf.constant([1.0, 2.0, 3.0, 4.0, 5.0, 6.0], shape=[3, 2])
    c.append(tf.matmul(a, b))
with tf.device('/cpu:0'):
  sum = tf.add_n(c)
# 新建session，log_device_placement=True 即 打印设备分配日志
sess = tf.Session(config=tf.ConfigProto(log_device_placement=True))
# Runs the op.
print(sess.run(sum))
```

以下输出：

```
Device mapping:
/job:localhost/replica:0/task:0/device:GPU:0 -> device: 0, name: Tesla K20m, pci bus
id: 0000:02:00.0
/job:localhost/replica:0/task:0/device:GPU:1 -> device: 1, name: Tesla K20m, pci bus
id: 0000:03:00.0
/job:localhost/replica:0/task:0/device:GPU:2 -> device: 2, name: Tesla K20m, pci bus
id: 0000:83:00.0
/job:localhost/replica:0/task:0/device:GPU:3 -> device: 3, name: Tesla K20m, pci bus
id: 0000:84:00.0
Const_3: /job:localhost/replica:0/task:0/device:GPU:3
Const_2: /job:localhost/replica:0/task:0/device:GPU:3
MatMul_1: /job:localhost/replica:0/task:0/device:GPU:3
Const_1: /job:localhost/replica:0/task:0/device:GPU:2
Const: /job:localhost/replica:0/task:0/device:GPU:2
MatMul: /job:localhost/replica:0/task:0/device:GPU:2
AddN: /job:localhost/replica:0/task:0/cpu:0
[[  44.   56.]
 [  98.  128.]]
```



# ss


cifar10的多GPU利用率极低



# 测试

## 单机单卡 VS 单机多卡 VS 多机多卡


- two GPUs are more than three times faster than a single GPU


## 多卡同步 VS 多卡异步


同步更新和异步更新

> in-graph模式和between-graph模式都支持同步和异步更新。


- 在同步更新的时， 每次梯度更新，都要等所有分发出去的数据计算完成后，返回结果之后，把梯度累加算了均值之后，再更新参数。 这样的好处是loss的下降比较稳定， 但是这个的坏处也很明显， 处理的速度取决于最慢的那个分片计算的时间。
- 在异步更新时， 所有的计算节点，各自算自己的， 更新参数也是自己更新自己计算的结果， 这样的优点就是计算速度快， 计算资源能得到充分利用，但是缺点是loss的下降不稳定， 抖动大。

在数据量较小的情况下， 各个节点的计算能力比较均衡， 推荐使用同步模式；在数据量很大情况下，各个主机的计算性能掺差不齐的情况下，推荐使用异步的方式。

## 



# 扩展阅读

- [分布式TensorFlow多主机多GPU原理与实现](https://blog.csdn.net/yjk13703623757/article/details/80956268)