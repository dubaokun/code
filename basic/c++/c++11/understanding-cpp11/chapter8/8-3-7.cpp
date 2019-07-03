#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <iomanip>
using namespace std;

int main(){
    //
    locale lc("en_US.UTF-8");
    //bool can_cvt = has_facet<codecvt<wchar_t, char, mbstate_t>>(lc);
    bool can_cvt = has_facet<codecvt<wchar_t, char, mbstate_t>>(lc);
    if (!can_cvt) {
        cout << "Do not have facet!" << endl;
        return 1;
    }
    else{
        auto & cvt = use_facet<codecvt<wchar_t, char, mbstate_t>>(lc);
        wstring_convert<cvt_facet> converter;
        u8string u8s = "\u4F60\u597D\u554A";
        wstring ws = converter.from_bytes(u8s);
        u8string u8s2 = converter.to_bytes(ws);
        cout << u8s2 << endl;
    }
}
