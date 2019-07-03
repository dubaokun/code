#include <iostream>
#include <locale>
using namespace std;

int main(){
    // 定义一个locale并查询该locale是否支持一些facet
    locale lc("en_US.UTF-8");
    bool can_cvt = has_facet<codecvt<wchar_t, char, mbstate_t>>(lc);
    if (!can_cvt)
        cout << "Do not support char-wchar_t facet!" << endl;

    can_cvt = has_facet<codecvt<char16_t, char, mbstate_t>>(lc);
    if (!can_cvt) 
        cout << "Do not support char-char16 facet!" << endl;

    can_cvt = has_facet<codecvt<char32_t, char, mbstate_t>>(lc);
    if (!can_cvt) 
        cout << "Do not support char-char32 facet!" << endl;

    can_cvt = has_facet<codecvt<char, char, mbstate_t>>(lc);
    if (!can_cvt) 
        cout << "Do not support char-char facet!" << endl;

    return 0;
}
