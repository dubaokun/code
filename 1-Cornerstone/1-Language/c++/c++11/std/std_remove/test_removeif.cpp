#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

//该方法实现对3的倍数的元素的过滤
//参数是容器中的元素，注意返回值类型
bool RemoveItem(int item)
{
    if (item%3 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char* argv[])
{
    std::vector<int> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(6);
    vec.push_back(8);
    vec.push_back(12);
    vec.push_back(33);
    vec.push_back(22);
//第三个参数是使用函数指针的方法调用，参数由系统自动传递
//返回值为真则清除，假则不清除
   vec.erase( std::remove_if(vec.begin(),vec.end(),RemoveItem), vec.end() );

    std::vector<int>::iterator iter;
    for (iter = vec.begin(); iter != vec.end(); iter++)
    {
        printf("%d\n",(*iter));
    }

    return 0;
}
