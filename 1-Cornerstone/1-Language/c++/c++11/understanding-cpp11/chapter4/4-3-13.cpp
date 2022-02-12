#include <type_traits>
#include <iostream>
using namespace std;

int i = 1;
int & j = i;
int * p = &i;
const int k = 1;

int main() {
    decltype(i) & var1 = i; 
    decltype(j) & var2 = i;     // 冗余的&, 被忽略 
        
    cout << is_lvalue_reference<decltype(var1)>::value << endl;     // 1, 是左值引用

    cout << is_rvalue_reference<decltype(var2)>::value << endl;     // 0, 不是右值引用
    cout << is_lvalue_reference<decltype(var2)>::value << endl;     // 1, 只是左值引用

    //decltype(p)* var3 = &i;     // 无法通过编译
    decltype(p)* var3 = &p;     // var3的类型是int**

    auto* v3 = p;               // v3的类型是int*
    v3 = &i;

    const decltype(k) var4 = 1; // 冗余的const，被忽略 
}
