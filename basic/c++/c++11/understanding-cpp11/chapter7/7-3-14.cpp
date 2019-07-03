#include <vector>
#include <algorithm>
using namespace std;

vector<int> nums;
vector<int> largeNums;

class LNums{
    public:
        LNums(int u): ubound(u){}

        void operator () (int i) const
        {
            if (i > ubound)
                largeNums.push_back(i);
        }
    private:
        int ubound;
};

void Above(int ubound) {
    // 传统的for循环
    for (auto itr = nums.begin(); itr != nums.end(); ++itr) {
        if (*itr >= ubound)
            largeNums.push_back(*itr);
    }

    // 使用functor
    for_each(nums.begin(), nums.end(), LNums(ubound));

    // 使用lambda函数和算法for_each
    for_each(nums.begin(), nums.end(), [=](int i){
            if (i > ubound)
                largeNums.push_back(i);
            });

}

