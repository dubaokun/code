#include <typeinfo>
#include <iostream>
using namespace std;

int main() {
    int i;
    decltype(i) j = 0; 
    cout << typeid(j).name() << endl;   // 打印出"i", g++表示integer

    float a;
    double b;
    decltype(a + b) c;
    cout << typeid(c).name() << endl;   // 打印出"d", g++表示double
}
