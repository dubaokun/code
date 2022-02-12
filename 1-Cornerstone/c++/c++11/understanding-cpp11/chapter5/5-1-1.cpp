#include <iostream>
using namespace std;

namespace T{
    enum Type { General, Light, Medium, Heavy };
}

namespace {
    enum Category { General = 1, Pistol, MachineGun, Cannon };
}

int main() {
    T::Type t = T::Light;
    if (t == General)   // 忘记使用namespace
        cout << "General Weapon" << endl;
    return 0;
}


