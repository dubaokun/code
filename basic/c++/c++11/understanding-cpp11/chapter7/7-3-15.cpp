#include <vector>
#include <algorithm>
using namespace std;

extern vector<int> nums;

void OneCond(int val){
   // 传统的for循环
   for (auto i = nums.begin(); i != nums.end(); i++)
      if (*i == val) break;

   // 内置的functor(template) equal_to, 通过bind2nd使其成为单参数调用的functor
   find_if(nums.begin(), nums.end(), bind2nd(equal_to<int>(), val));

   // 使用lambda函数
   find_if(nums.begin(), nums.end(), [=](int i) {
           return i == val;
           });
}

