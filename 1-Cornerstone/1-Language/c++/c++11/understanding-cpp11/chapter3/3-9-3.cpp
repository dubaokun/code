#include <iostream>
using namespace std;

namespace Jim {
    inline namespace Basic {
        struct Knife{ Knife() { cout << "Knife in Basic." << endl; } };
        class CorkScrew{};
    }
    inline namespace Toolkit {
        template<typename T> class SwissArmyKnife{};
    }
    // ...
    namespace Other{
        Knife b;            // Knife in Basic
        struct Knife{ Knife() { cout << "Knife in Other" << endl;} };
        Knife c;            // Knife in Other 
        Basic::Knife k;     // Knife in Basic
    }
}

// 这是LiLei在使用Jim的库
namespace Jim {
    template<> class SwissArmyKnife<Knife>{};   // 编译通过
}

using namespace Jim;
int main() {
    SwissArmyKnife<Knife> sknife;
}

