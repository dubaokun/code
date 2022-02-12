#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

static const string StrTradition = "tradition expression: ";
static const string StrLambda = "lambda expression: "; 

// 传统声明、定义函数的方式
bool cmp(int a, int b)
{
    return  a < b;
}

void show(const vector<int>& vec, const string& str) {
    cout << str << endl;
    for (int i : vec) {
        cout << i << " ";
    }
    cout << endl;
} 

int main()
{
    vector<int> myvec{ 3, 2, 5, 7, 3, 2 };
    vector<int> lbvec(myvec);

    // 传统使用函数的方式，本地仅仅使用
    sort(myvec.begin(), myvec.end(), cmp); // 旧式做法
    show(myvec, StrTradition);

    // lambda表达式，声明、定义、使用在同一个地方
    sort(lbvec.begin(), lbvec.end(), [](int a, int b) -> bool { return a < b; });   // Lambda表达式
    show(myvec, StrLambda); 
}
