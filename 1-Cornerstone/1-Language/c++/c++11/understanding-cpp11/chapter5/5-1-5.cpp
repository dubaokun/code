#include <iostream>
using namespace std;

enum class Type { General, Light, Medium, Heavy };
enum class Category { General = 1, Pistol, MachineGun, Cannon };

int main() {
    Type t = Type::Light;
    t = General;                    // 编译失败，必须使用强类型名称
    if (t == Category::General)     // 编译失败，必须使用Type中的General
        cout << "General Weapon" << endl;
    if (t > Type::General)          // 通过编译
        cout << "Not General Weapon" << endl;
    if (t > 0)                      // 编译失败，无法转换为int类型
        cout << "Not General Weapon" << endl;
    if ((int)t > 0)                 // 通过编译
        cout << "Not General Weapon" << endl;
    cout << is_pod<Type>::value << endl;        // 1
    cout << is_pod<Category>::value << endl;    // 1
    return 0;
}
