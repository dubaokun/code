# -*- encoding:utf-8 -*-
#利用Python实现感知机算法的对偶形式
 
"""
Created on 2017.6.7
@author: Ada
"""
 
import numpy as np
import matplotlib.pyplot as plt
 
# 创建数据集
def createdata():
    samples=np.array([[3,-3],[4,-3],[1,1],[1,2]])
    labels=np.array([-1,-1,1,1])
    return samples,labels
 
# 训练感知机模型
class Perceptron:
    def __init__(self, x, y, a=1):
        self.x = x                                                              # matrix=4 X 2
        self.y = y                                                              # matrix=4 X 1
        self.w = np.zeros((1, x.shape[0]))                                      # matrix=1 X 4 | 权值参数
        self.b = 0                                                              # 偏置
        self.a = 1                                                              # 学习率 
        self.numsamples = self.x.shape[0]
        self.numfeatures = self.x.shape[1]
        self.gMatrix = self.cal_gram(self.x)
 
    def cal_gram(self, x):
        gMatrix = np.zeros((self.numsamples, self.numsamples))
        for i in xrange(self.numsamples):
            for j in xrange(self.numsamples):
                gMatrix[i][j] = np.dot(self.x[i,:], self.x[j,:])
        return gMatrix                                                          # matrix=4X4
 
    def sign(self, w, b, key):
        y = np.dot(w * self.y, self.gMatrix[:,key]) + b                         # param1: 1 X 4; param2: 4 X 1
        return int(y)
 
    def update(self,i):
        self.w[i,] = self.w[i,] + self.a
        self.b = self.b + self.y[i] * self.a
 
    def cal_w(self):
        w=np.dot(self.w * self.y, self.x)
        return w
 
    def train(self):
        isFind = False
        while not isFind:
            count = 0
            for i in range(self.numsamples):
                tmpY =s elf.sign(self.w, self.b, i)
                if tmpY * self.y[i] <= 0:                                            # 如果是一个误分类实例点
                    print '误分类点为：',self.x[i,:],'此时的w和b为：',self.cal_w(),',',self.b
                    count+=1
                    self.update(i)
            if count==0:
                print '最终训练得到的w和b为：',self.cal_w(),',',self.b
                isFind=True
        weights=self.cal_w()
        return weights,self.b
 
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
        y=(-self.b-self.w[:,0]*x)/self.w[:,1]
        return y
 
    def Show(self):
        plt.show()
 
 
if __name__ == '__main__':
 
    samples,labels=createdata()
    myperceptron=Perceptron(x=samples,y=labels)
    weights,bias=myperceptron.train()
    Picture=Picture(samples,weights,bias)
    Picture.Show()
