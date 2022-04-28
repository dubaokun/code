from __future__ import division
from __future__ import print_function

import time
import tensorflow as tf

from utils import *
from models import GCN, MLP

# Set random seed
seed = 123
np.random.seed(seed)
tf.set_random_seed(seed)

# Settings
flags = tf.app.flags
FLAGS = flags.FLAGS
flags.DEFINE_string('dataset', 'cora', 'Dataset string.')  # 'cora', 'citeseer', 'pubmed'
flags.DEFINE_string('model', 'gcn', 'Model string.')  # 'gcn', 'gcn_cheby', 'dense'
flags.DEFINE_float('learning_rate', 0.01, 'Initial learning rate.')
flags.DEFINE_integer('epochs', 200, 'Number of epochs to train.')
# 第一层的输出维度
flags.DEFINE_integer('hidden1', 16, 'Number of units in hidden layer 1.')
flags.DEFINE_float('dropout', 0.5, 'Dropout rate (1 - keep probability).')
# 权值衰减：防止过拟合
# loss计算方式（权值衰减+正则化）：self.loss += FLAGS.weight_decay * tf.nn.l2_loss(var)
flags.DEFINE_float('weight_decay', 5e-4, 'Weight for L2 loss on embedding matrix.')
flags.DEFINE_integer('early_stopping', 10, 'Tolerance for early stopping (# of epochs).')
# K阶的切比雪夫近似矩阵的参数k
flags.DEFINE_integer('max_degree', 3, 'Maximum Chebyshev polynomial degree.')

Step = 1

def show(data, act):
  print('Step-s = ', act)
  print('***********************************************************************')
  print(type(data))
  print('=========')
  print(data.shape)
  print('=========')
  print(data)
  print('***********************************************************************')
  print('Step-e = ', act)
  # print(adj.shape)

def show2(data, act):
  print('Step-s = ', act)
  print('***********************************************************************')
  print(type(data))
  print('=========')
  print(np.size(data))
  print('=========')
  print(data)
  print('=========')
  print(type(data[0]))
  print(data[0].shape)
  print('=========')
  print(type(data[1]))
  print(data[1].shape)
  print('=========')
  print(type(data[2]))
  print(np.size(data[2]))
  print(data[2])
  print('=========')
  print('***********************************************************************')
  print('Step-e = ', act)
  # print(adj.shape)

def show3(data, act):
  print('Step-s = ', act)
  print('***********************************************************************')
  print(type(data))
  print('=========')
  print(np.size(data))
  print('=========')
  print(data)
  print('=========')
  print(type(data[0]))
  print(np.size(data[0]))
  print(data[0][0])
  print(data[0][1])
  print(data[0][2])
  print('=========')
  print('=========')
  print('***********************************************************************')
  print('Step-e = ', act)
  

# Load data
adj, features, y_train, y_val, y_test, train_mask, val_mask, test_mask = load_data(FLAGS.dataset)
show(features, "features")
show(adj, 'adj')
# Some preprocessing
features = preprocess_features(features)
show2(features, "features")
if FLAGS.model == 'gcn':
    support = [preprocess_adj(adj)]
    show3(support, 'adj')
    num_supports = 1
    model_func = GCN
elif FLAGS.model == 'gcn_cheby':
    support = chebyshev_polynomials(adj, FLAGS.max_degree)
    num_supports = 1 + FLAGS.max_degree
    model_func = GCN
elif FLAGS.model == 'dense':
    support = [preprocess_adj(adj)]  # Not used
    num_supports = 1
    model_func = MLP
else:
    raise ValueError('Invalid argument for model: ' + str(FLAGS.model))

# Define placeholders
placeholders = {
    # 由于邻接矩阵是稀疏的，并且用LIL格式表示，因此定义为一个tf.sparse_placeholder(tf.float32)，可以节省内存
    'support': [tf.sparse_placeholder(tf.float32) for _ in range(num_supports)],
    # features也是稀疏矩阵，也用LIL格式表示，因此定义为tf.sparse_placeholder(tf.float32)，维度(2708, 1433)
    'features': tf.sparse_placeholder(tf.float32, shape=tf.constant(features[2], dtype=tf.int64)),
    'labels': tf.placeholder(tf.float32, shape=(None, y_train.shape[1])),
    'labels_mask': tf.placeholder(tf.int32),
    'dropout': tf.placeholder_with_default(0., shape=()),
    'num_features_nonzero': tf.placeholder(tf.int32)  # helper variable for sparse dropout
}

# 构建计算图
# print(features[2][1])
# 1433
model = model_func(placeholders, input_dim=features[2][1], logging=True)

# print("GCN output_dim:",model.output_dim)
# GCN output_dim: 7

# Initialize session
sess = tf.Session()


# Define model evaluation function
def evaluate(features, support, labels, mask, placeholders):
    t_test = time.time()
    feed_dict_val = construct_feed_dict(features, support, labels, mask, placeholders)
    outs_val = sess.run([model.loss, model.accuracy], feed_dict=feed_dict_val)
    return outs_val[0], outs_val[1], (time.time() - t_test)


# Init variables
sess.run(tf.global_variables_initializer())

cost_val = []

# Train model
for epoch in range(FLAGS.epochs):

    t = time.time()
    # Construct feed dictionary
    feed_dict = construct_feed_dict(features, support, y_train, train_mask, placeholders)
    feed_dict.update({placeholders['dropout']: FLAGS.dropout})

    # Training step
    outs = sess.run([model.opt_op, model.loss, model.accuracy], feed_dict=feed_dict)

    # Validation
    cost, acc, duration = evaluate(features, support, y_val, val_mask, placeholders)
    cost_val.append(cost)

    # Print results
    print("Epoch:", '%04d' % (epoch + 1), "train_loss=", "{:.5f}".format(outs[1]),
          "train_acc=", "{:.5f}".format(outs[2]), "val_loss=", "{:.5f}".format(cost),
          "val_acc=", "{:.5f}".format(acc), "time=", "{:.5f}".format(time.time() - t))

    if epoch > FLAGS.early_stopping and cost_val[-1] > np.mean(cost_val[-(FLAGS.early_stopping+1):-1]):
        print("Early stopping...")
        break

print("Optimization Finished!")

# Testing
test_cost, test_acc, test_duration = evaluate(features, support, y_test, test_mask, placeholders)
print("Test set results:", "cost=", "{:.5f}".format(test_cost),
      "accuracy=", "{:.5f}".format(test_acc), "time=", "{:.5f}".format(test_duration))
