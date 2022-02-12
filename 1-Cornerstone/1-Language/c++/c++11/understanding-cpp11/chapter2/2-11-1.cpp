#include <iostream>
using namespace std;

// 定义一个函数模板 
template <typename T> void TempFun(T a) {
    cout << a << endl;
}

int main() {
    TempFun(1);     // 1, (实例化为TempFun<const int>(1))
    TempFun("1");   // 1, (实例化为TempFun<const char *>("1"))
}
