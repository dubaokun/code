import matplotlib.pyplot as plt
import numpy as np 

#函数
g=lambda z:(np.exp(z)-np.exp(-z))/(np.exp(z)+np.exp(-z))

start=-10 #输入需要绘制的起始值（从左到右）
stop=10 #输入需要绘制的终点值
step=0.01#输入步长
num=(stop-start)/step #计算点的个数
num = int(num)                         # 显式的类型转换
x = np.linspace(start,stop,num)
y = g(x)

fig=plt.figure(1)
plt.plot(x, y,label='tanh')
plt.grid(True)#显示网格

plt.legend()#显示旁注
plt.show()
