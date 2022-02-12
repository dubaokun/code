#include <iostream>
#include <cstring>
using namespace std;

int main(){
    char utf8[] = u8"\u4F60\u597D\u554A";
    char16_t utf16[] = u"hello";
    char32_t utf32[] = U"hello equals \u4F60\u597D\u554A";

    cout << utf8 <<  endl;
    cout << utf16 << endl;
    cout << utf32 << endl;

#if 0
    char32_t u2[] = u"hello";   // Error
    char u3[] = U"hello";       // Error
    char16_t u4 = u8"hello";    // Error
#endif
}
