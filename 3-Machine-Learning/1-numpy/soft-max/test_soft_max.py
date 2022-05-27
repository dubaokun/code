import numpy as np

def softmax(x):
  f_x = np.exp(x) / np.sum(np.exp(x))
  return f_x

def softmax1(x):
  y = np.exp(x - np.max(x))
  f_x = y / np.sum(np.exp(x))
  return f_x

data = [15, 30, 15, 35]
tmp = softmax(data)
print(tmp)
tmp1 = softmax1(data)
print(tmp1)
