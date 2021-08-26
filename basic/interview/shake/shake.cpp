#include <iostream>
using namespace std;
 
const int ROW = 4;
const int COLUMN = 3;
const string space = " ";
 
void setSnakeMatrix(int array[ROW][COLUMN], int start)
{
    int x = 0, y = 0;
    
    while(start<ROW*COLUMN)
    {
        //上行：从左向右
        while(y+1<COLUMN && array[x][y+1]==0)
        {
            array[x][y++] = start++;
        }
        //右列：从上向下
        while(x+1<ROW && array[x+1][y]==0)
        {
            array[x++][y] = start++;
        }
        //下行：从右向左
        while(y-1>=0 && array[x][y-1]==0)
        {
            array[x][y--] = start++;
        }
        //左列：从下向上
        while(x-1>=0 && array[x-1][y]==0)
        {
            array[x--][y] = start++;
        }
    }
    //最后一个
    array[x][y] = start;
    
}
 
void displayMatrix(int array[ROW][COLUMN])
{
    for(int row = 0; row<ROW; row++)
    {
        for (int column = 0; column<COLUMN; column++)
        {
            if(array[row][column]>=10)
            {
                cout<<array[row][column]<<space;
            }else{
                cout<<array[row][column]<<space<<space;
            }
        }
        cout<<endl;
    }
}
 
int main() {
    //定义二维数组，初始化全为0，由于蛇形矩阵从1开始递增，所以全部元素都不会为0，
    //因此可以将0作为判断条件
    int array[ROW][COLUMN] = {0};
    //设置蛇形矩阵
    setSnakeMatrix(array, 1);
    //输出
    displayMatrix(array);
    return 0;
}
