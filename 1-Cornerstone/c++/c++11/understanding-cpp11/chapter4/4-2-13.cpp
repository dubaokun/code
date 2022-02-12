#include <vector>
using namespace std;

void fun(auto x =1){}  // 1: auto函数参数，无法通过编译

struct str{
    auto var = 10;   // 2: auto非静态成员变量，无法通过编译
};

int main() {
    char x[3];
    auto y = x;
    auto z[3] = x; // 3: auto数组，无法通过编译

    // 4: auto模板参数（实例化时），无法通过编译
    vector<auto> x = {1};
}
