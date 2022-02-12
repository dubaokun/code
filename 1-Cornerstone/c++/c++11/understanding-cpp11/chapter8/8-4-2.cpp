#include <iostream>
using namespace std;

int main(){
    cout << u8R"(\u4F60,\n
         \u597D)" << endl;
    cout << u8R"(你好)" << endl;
    cout << sizeof(u8R"(hello)") << "\t" << u8R"(hello)" << endl;
    cout << sizeof(uR"(hello)") << "\t" << uR"(hello)" << endl;
    cout << sizeof(UR"(hello)") << "\t" << UR"(hello)" << endl;
    return 0;
}
