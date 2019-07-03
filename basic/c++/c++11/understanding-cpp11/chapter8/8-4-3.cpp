#include <iostream>
using namespace std;

int main() {
    char u8string[] = u8R"(你好)" " = hello";
    cout << u8string << endl;   // 输出"你好 = hello"
    cout << sizeof(u8string) << endl;   // 15
    return 0;
}
