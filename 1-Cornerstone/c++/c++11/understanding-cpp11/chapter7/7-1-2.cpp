#include <iostream>
using namespace std;

void f(char *p) {
    cout << "invoke f(char*)" << endl;
}

void f(int) {
    cout << "invoke f(int)" << endl;
}

int main()
{
    f(nullptr);    // 调用f(char*)版本
    f(0);          // 调用f(int)版本
    return 0;
}
