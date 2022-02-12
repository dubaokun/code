#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> nums;

void Add(const int val){
    auto print = [&]{
        for (auto s: nums){ cout << s << '\t'; }
        cout<< endl;
    };

    // 传统的for循环方式
    for (auto i = nums.begin(); i != nums.end(); ++i){
        *i = *i + val;
    }
    print();

    // 试一试for_each及内置functor
    for_each(nums.begin(), nums.end(), bind2nd(plus<int>(), val));
    print();

    // 实际这里我们需要使用STL的一个变动性算法：transform 
    transform(nums.begin(), nums.end(), nums.begin(), bind2nd(plus<int>(), val));
    print();

    // 不过在lambda的支持下，我们还是可以只使用for_each
    for_each(nums.begin(), nums.end(), [=](int &i){
                i += val;
            });
    print();
}


int main(){
    for (int i = 0; i < 10; i++){
        nums.push_back(i);
    }
    Add(10);
    return 1;
}
