#include <vector>
#include <algorithm>
using namespace std;

extern vector<int> nums;

void TwoCond(int low, int high) {
   // 传统的for循环
   for (auto i = nums.begin(); i != nums.end(); i++)
      if (*i >= low && *i < high) break;

   // 利用了三个内置的functor，以及非标准的compose2
   find_if(nums.begin(), nums.end(), 
           compose2(logical_and<bool>(),
               bind2nd(less<int>(), high), 
               bind2nd(greater_equal<int>(), low)));

   // 使用lambda函数
   find_if(nums.begin(), nums.end(), [=](int i) {
           return i >= low && i < high;
           });
}

