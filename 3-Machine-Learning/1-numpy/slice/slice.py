import numpy as np

a = np.arange(10)
s = slice(2, 7, 2) # 从索引2开始到索引7停止，步长是2
print('=========================')
print(a)
print(s)
print(a[s])

