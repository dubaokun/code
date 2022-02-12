#include <cvt/wstring>
#include <codecvt>
#include <iostream>
using namespace std;

int main() {
    wstring_convert<codecvt_utf8<wchar_t>> myconv;
    string mbstring = myconv.to_bytes(L"Hello\n");
    cout << mbstring;
}
