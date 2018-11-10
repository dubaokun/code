#include <iostream>
using namespace std;
 
//物品数据结构
typedef struct commodity
{
    int value;  //价值
    int weight; //重量
}commodity;
 
const int N = 3;  //物品个数
const int W = 50; //背包的容量
 
//初始物品信息
commodity goods[N+1]={{0,0},{60,10},{100,20},{120,30}};
int select[N+1][W+1];
 
int max_value();
 
int main()
{
    int maxvalue = max_value();
    cout<<"The max value is: ";
    cout<<maxvalue<<endl;
    int remainspace = W;
    //输出所选择的物品列表：
    for(int i=N; i>=1; i--)
    {
        if (remainspace >= goods[i].weight)
        {
             if ((select[i][remainspace]-select[i-1][remainspace-goods[i].weight]==goods[i].value))
             {
                 cout << "item " << i << " is selected!" << endl;
                 remainspace = remainspace - goods[i].weight;//如果第i个物品被选择，那么背包剩余容量将减去第i个物品的重量 ;
             }
        }
    }
    return 0;
}
int max_value()
{
    //初始没有物品时候，背包的价值为0
    for(int w=1;w<=W;++w)
        select[0][w] = 0;
    for(int i=1;i<=N;++i)
    {
        select[i][0] = 0;  //背包容量为0时，最大价值为0
           for(int w=1;w<=W;++w)
           {
               if(goods[i].weight <= w)  //当前物品i的重量小于等于w，进行选择
               {
                   if( (goods[i].value + select[i-1][w-goods[i].weight]) > select[i-1][w])
                    select[i][w] = goods[i].value + select[i-1][w-goods[i].weight];
                   else
                    select[i][w] = select[i-1][w];
               }
               else //当前物品i的重量大于w，不选择
                 select[i][w] = select[i-1][w];
           }
    }
    return select[N][W];  //最终求得最大值
}
