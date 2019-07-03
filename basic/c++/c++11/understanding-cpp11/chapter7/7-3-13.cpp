#include <vector>
#include <algorithm>
using namespace std;

vector<int> nums;
vector<int> largeNums;

const int ubound = 10;

inline void LargeNumsFunc(int i){
    if (i > ubound)
        largeNums.push_back(i);
}

void Above() {
    // 传统的for循环
    for (auto itr = nums.begin(); itr != nums.end(); ++itr) {
        if (*itr >= ubound)
            largeNums.push_back(*itr);
    }

    // 使用函数指针
    for_each(nums.begin(), nums.end(), LargeNumsFunc);

    // 使用lambda函数和算法for_each
    for_each(nums.begin(), nums.end(), [=](int i){
            if (i > ubound)
                largeNums.push_back(i);
            });
}

