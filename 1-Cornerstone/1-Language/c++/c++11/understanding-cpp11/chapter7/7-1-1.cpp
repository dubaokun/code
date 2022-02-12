#include <iostream>
using namespace std;

void f(char* c) {
    cout << "invoke f(char*)" << endl;
}

void f(int i) { 
    cout << "invoke f(int)" << endl;
}

int main() {
    f(0);
    // f(NULL); // 注意：如用gcc编译，NULL转化为内部标示__null，该句会编译失败。
    f((char*)0);
}
