//
//  main.cpp
//  linear_regression_house_price
//
//  Created by zsp on 2018/7/14.
//  Copyright © 2018年 zsp. All rights reserved.
//
 
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
 
const int SAMPLE = 27;
const int PARAMETER = 12;
 
double hypoVal(double para[], double fea[], int count);
double costVal(double para[], double lab[], int amount, double allX[][PARAMETER + 1]);
 
int main()
{
    //文本操作，读入数据
    fstream infile;
    infile.open("data.txt");
    if (!infile)
    {
        cout << "can't open file!" << endl;
        return -1;
    }
    //二维数组储存数据
    double X[SAMPLE + 1][PARAMETER + 1];    //features matrix
    for (int i = 0; i < SAMPLE + 1; i++)
    {
        for (int j = 0; j < PARAMETER + 1; j++)
        {
            infile >> X[i][j];
        }
    }
    infile.close();
    //验证数据是否写入
    for (int i = 0; i < SAMPLE + 1; i++)
    {
        for (int j = 0; j < PARAMETER + 1; j++)
            cout << X[i][j] << " ";
        cout << endl;
    }
    //特征缩放
    
    //留一法，得到训练集X[0]~X[26]和测试集X[27]
    double y[SAMPLE] = { 0 };      //labels vector
    double theta[PARAMETER] = { 0 };   //parameters vector
    double a = 0.0001;    //set learning rate as 0.0001
    int cnt = 0;        //to count the times of loop
    for (int i = 0; i < SAMPLE; i++)
    {
        y[i] = X[i][PARAMETER];
    }
    double h =  hypoVal(theta, X[0], PARAMETER); //hypothesis function
    double cost = costVal(theta, y, SAMPLE, X); //cost function
    
    //梯度下降法求theta
    double temp[PARAMETER] = { 0 };    //used for simultaneously updating theta parameters
    double der[PARAMETER] = { 0 };  //the derivative term
    double tempCost = 0;       //break the loop when tempCost - cost is small enough
    do {
        tempCost = cost;
        double sum = 0;
        for (int j = 0; j < PARAMETER; j++)
        {
            for (int i = 0; i < SAMPLE; i++)
            {
                sum += (hypoVal(theta, X[i], PARAMETER) - y[i]) * X[i][j];
            }
            der[j] = (1.0 / double (PARAMETER)) * sum;
            temp[j] = theta[j] - a * der[j];
            sum = 0;
        }
        cout << "now the theta parameters are: ";
        for (int i = 0; i < PARAMETER; i++)
        {
            theta[i] = temp[i];
            cout << theta[i] << " ";
        }
        cout << endl;
        cost = costVal(theta, y, SAMPLE, X);        //new cost value
        cnt++;
    } while (tempCost - cost > 0.00001);
    
    //测试集进行测试
    cout << "共进行" << cnt << "次梯度下降法" << endl;
    h = hypoVal(theta, X[SAMPLE - 1], PARAMETER);
    cout << "对测试数据预测值为：" << h << "，真实值为：" << y[SAMPLE - 1] << endl;
    return 0;
}
 
double hypoVal(double para[], double fea[], int count)  //the value of hypothesis function
{
    double hy = 0;
    for (int i = 0; i < count; i++)
    {
        hy += para[i] * fea[i];
    }
    return hy;
}
double costVal(double para[], double lab[], int amount, double allX[][PARAMETER + 1])    //the value of cost function
{
    double sum = 0;
    for (int i = 0; i < amount; i++)
    {
        sum += pow((hypoVal(para, allX[i], PARAMETER) - lab[i]), 2);
    }
    cout << "costVal now is : " << (1.0/(2.0 * (double) amount)) * sum << endl;
    return double(1.0/(2.0 * (double) amount)) * sum;
}
