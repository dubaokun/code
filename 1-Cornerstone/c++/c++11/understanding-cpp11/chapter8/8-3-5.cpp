#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <iomanip>
using namespace std;

int main()
{
    // UTF-8字符串, "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9d\x84\x8b";
    ofstream("text.txt") << u8"z\u00df\u6c34\U0001d10b"; 
                                           
    wifstream fin("text.txt");
    // 该locale的facet - codecvt<wchar_t, char, mbstate_t>
    // 可以将UTF-8转化为UTF-32
    fin.imbue(locale("en_US.UTF-8")); 

    cout << "The UTF-8 file contains the following wide characters: \n";
    for(wchar_t c; fin >> c; )
        cout << "U+" << hex << setw(4) << setfill('0') << c << '\n';
}
