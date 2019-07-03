#include <type_traits>
#include <iostream>
using namespace std;

// 有的时候，你会发现这是面试题
int (*(*pf())())() {
    return nullptr;
}

// auto (*)() -> int(*) () 一个返回函数指针的函数(假设为a函数)
// auto pf1() -> auto (*)() -> int (*)() 一个返回a函数的指针的函数
auto pf1() -> auto (*)() -> int (*)() {
    return nullptr;
}

int main() {
    cout << is_same<decltype(pf), decltype(pf1)>::value << endl;    // 1
}
