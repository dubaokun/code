#include <iostream>
using namespace std;

namespace Jim {
#if __cplusplus == 201103L
    inline 
#endif
    namespace cpp11{
        struct Knife{ Knife() { cout << "Knife in c++11." << endl; } };
        // ...
    }

#if __cplusplus < 201103L
    inline 
#endif
    namespace oldcpp{
        struct Knife{ Knife() { cout << "Knife in old c++." << endl; } };
        // ...
    }
}

using namespace Jim;
int main() {
    Knife a;            // Knife in c++11. (默认版本)
    cpp11::Knife b;     // Knife in c++11. (强制使用cpp11版本)
    oldcpp::Knife c;    // Knife in old c++. (强制使用oldcpp11版本)
}
