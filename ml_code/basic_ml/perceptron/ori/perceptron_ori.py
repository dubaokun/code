# -*- encoding:utf-8 -*-
# 利用Python实现感知机算法的原始形式
 
"""
Created on 2018-03-29
@author: Sam
Functon:
	1 np.array 
	2 np.zeros
	3 get one row or colum  
	3 np.reshape
"""
 
import numpy as np
import matplotlib.pyplot as plt
 
# 创建数据集
def createdata():
    samples = np.array([[3,-3], [4,-3], [1,1], [1,2]])			# 4 x 2
    labels=[-1,-1,1,1]										# 4 x 1
    return samples,labels
 
# 训练感知机模型
class Perceptron:
    def __init__(self,x,y,a=1):
        self.x=x
        self.y=y
        self.w=np.zeros((x.shape[1],1))						# 权值初始化权重，w1,w2均为0, 2 x 1
        self.b=0											# 偏置初始化值，0
        self.a=1											# 学习率
        self.numsamples=self.x.shape[0]
        self.numfeatures=self.x.shape[1]
 
    def sign(self,w,b,x):
        y=np.dot(x,w)+b										# 点积: x=1X2；w=2X1
        return int(y)
 
    def update(self,label_i,data_i):
        tmp=label_i*self.a*data_i							# 1 x 2
        tmp=tmp.reshape(self.w.shape)						# 转置 2 x 1
        # 更新w和b
        self.w=tmp+self.w                                   # two matrix of 2X1 to add
        self.b=self.b+label_i*self.a
 
    def train(self):
        isFind=False
        step = 0
        while not isFind:
            count=0
            for i in range(self.numsamples):
                tmpY=self.sign(self.w,self.b,self.x[i,:])
                if tmpY*self.y[i]<=0:					#如果是一个误分类实例点
                    print 'step=', step, '误分类点为：',self.x[i,:],'此时的w和b为：',self.w,self.b
                    count+=1
                    self.update(self.y[i],self.x[i,:])
                    print 'step=', step, '迭代后的w和b为：',self.w,self.b
            if count==0:
                print 'step=', step, '最终训练得到的w和b为：',self.w,self.b
                isFind=True
            step+=1
        return self.w,self.b
 
#画图描绘
class Picture:
    def __init__(self,data,w,b):
        self.b=b
        self.w=w
        plt.figure(1)
        plt.title('Perceptron Learning Algorithm',size=14)
        plt.xlabel('x0-axis',size=14)
        plt.ylabel('x1-axis',size=14)
 
        xData=np.linspace(0,5,100)
        yData=self.expression(xData)
        plt.plot(xData,yData,color='r',label='sample data')
 
        plt.scatter(data[0][0],data[0][1],s=50)
        plt.scatter(data[1][0],data[1][1],s=50)
        plt.scatter(data[2][0],data[2][1],s=50,marker='x')
        plt.scatter(data[3][0],data[3][1],s=50,marker='x')
        plt.savefig('2d.png',dpi=75)
 
    def expression(self,x):
        y=(-self.b-self.w[0]*x)/self.w[1]                           #注意在此，把x0，x1当做两个坐标轴，把x1当做自变量，x2为因变量
        return y
 
    def Show(self):
        plt.show()

if __name__ == '__main__':
    samples,labels=createdata()
    myperceptron=Perceptron(x=samples,y=labels)
    weights,bias=myperceptron.train()
    Picture=Picture(samples,weights,bias)
    Picture.Show()
    
