//
//  main.cpp
//  linear_regression_house_price
//
//  Created by zsp on 2018/7/14.
//  Copyright © 2018年 zsp. All rights reserved.
//
 
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <cmath>

 
#define BUFFSIZE 2048
using namespace std;
const int SAMPLE = 1000001;
const int PARAMETER = 2;


using namespace std;
 
double hypoVal(double para[], double fea[], int count);
double costVal(double para[], double lab[], int amount, double allX[][PARAMETER + 1]);
 
int main()
{
    //文本操作，读入数据
    FILE *file= NULL;
    char buf[BUFFSIZE];
    if((file = fopen("data.txt", "r")) == NULL){
        cout << " open error " << endl;
    }
    double ** X = new double*[SAMPLE];
    for(int i = 0; i < SAMPLE; i++) {
      X[i] = new double[PARAMETER + 1];
    }
    int i = 0;
    while(fgets(buf, BUFFSIZE, file)){
        //cout << "________________BEGIN" << endl;
        int len= strlen(buf);
        buf[len-1]='\0';
        //cout << buf << endl;
        //cout << "======" << endl;
        string strs = buf;
        size_t pos = strs.find(" ");
        string temp = strs.substr(0, pos);
        strs = strs.substr(pos + 1, strs.size());
        //cout << temp << " " << strs << endl;
        double a1 = stold(temp);
        double a2 = stod(strs);
        //cout << a1 << " " << a2 << endl;
        X[i][0] = a1;
        X[i][1] = a2;
        //cout << X[i][0] << " " << X[i][1] << endl;
        i++;
        //cout << "________________END" << endl;

    }
    //验证数据是否写入
    /*
    cout << "Sample Print Start:" << endl;
    for (int i = 0; i < SAMPLE + 1; i++)
    {
        for (int j = 0; j < PARAMETER; j++)
            cout << X[i][j] << " ";
        cout << endl;
    }
    cout << "Sample Print End:" << endl;
    */
    //特征缩放
    
    //留一法，得到训练集X[0]~X[26]和测试集X[27]
    double y[SAMPLE] = { 0 };      //labels vector
    double theta[PARAMETER] = { 0.0001 };   //parameters vector
    double a = 0.0001;    //set learning rate as 0.0001
    int cnt = 0;        //to count the times of loop
    for (int i = 0; i < SAMPLE; i++)
    {
        y[i] = X[i][PARAMETER];
    }
    double h =  hypoVal(theta, X[0], PARAMETER); //hypothesis function
    double cost = costVal(theta, y, SAMPLE, (double (*)[3])X); //cost function
    
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
        cost = costVal(theta, y, SAMPLE, (double (*)[3])X);        //new cost value
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
    for (int i = 0; i < 100000; i++)
    {
        sum += pow((hypoVal(para, allX[i], PARAMETER) - lab[i]), 2);
    }
    cout << "costVal now is : " << (1.0/(2.0 * (double) amount)) * sum << endl;
    return double(1.0/(2.0 * (double) amount)) * sum;
}
