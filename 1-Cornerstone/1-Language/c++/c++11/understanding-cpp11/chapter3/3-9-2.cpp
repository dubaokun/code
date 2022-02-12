#include <iostream>
using namespace std;

namespace Jim {
    namespace Basic {
        struct Knife{ Knife() { cout << "Knife in Basic." << endl; } };
        class CorkScrew{};
    }
    namespace Toolkit{
        template<typename T> class SwissArmyKnife{};
    }
    // ...
    namespace Other{
        // ...
    }
    // 打开一些内部名字空间
    using namespace Basic;
    using namespace Toolkit;
}

// LiLei决定对该class进行特化
namespace Jim {
    template<> class SwissArmyKnife<Knife>{};   // 编译失败
}

using namespace Jim;
int main() {
    SwissArmyKnife<Knife> sknife;
}

