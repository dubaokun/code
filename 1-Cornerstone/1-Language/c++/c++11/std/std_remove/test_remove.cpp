#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>


int main(int argc, char* argv[])
{
    std::vector<int> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(6);
    vec.push_back(8);
    vec.push_back(12);
    vec.push_back(22);
    vec.push_back(33);
                
    //从前往后找出3的元素，并从vector中erase
    //remove第三个参数为常数的情况
    //vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
    std::vector<int>::iterator iter2 = std::remove(vec.begin(), vec.end(), 3);
    std::cout << *iter2 << std::endl;
    std::cout << "===============================" << std::endl;

    std::vector<int>::iterator iter = vec.begin();
    for (iter = vec.begin(); iter != vec.end(); iter++) {
        printf("%d\n",(*iter));
    }

    return 0;
}
