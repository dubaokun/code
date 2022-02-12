#include <string>
#include <iostream>

using namespace std;

void ValueTest() {
    int a = 123;
    auto f = [a]()mutable { cout << ++a << endl; }; // 不会报错
    cout << a << endl; // 输出：123
    f(); // 输出：124
    cout << a << endl;
}

void RefTest() {
    int a = 123;
    auto f = [&a]()mutable { cout << ++a << endl; }; // 不会报错
    cout << a << endl; // 输出：123
    f(); // 输出：124
    cout << a << endl;
}
 
int main(int argc, char ** argv) {
    ValueTest();
    cout << "========================" << endl;
    RefTest();
    return 0;
}
