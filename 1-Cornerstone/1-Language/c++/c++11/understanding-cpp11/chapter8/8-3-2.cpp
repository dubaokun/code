#include <iostream>
using namespace std;

int main() {
    char utf8[] = u8"\u4F60\u597D\u554A";
    char16_t utf16[] = u"\u4F60\u597D\u554A";


    cout << sizeof(utf8) << endl;       // 10字节
    cout << sizeof(utf16) << endl;      // 8字节

    cout << utf8[1] << endl;    // 输出不可见字符
    cout << utf16[1] << endl;   // 输出22909(0x597D)

}
