#include <type_traits>
#include <iostream>
using namespace std;

class NoCopyCstor {
public:
    NoCopyCstor() = default;

private:
    // 将拷贝构造函数声明为private成员并不提供实现
    // 可以有效阻止用户错用拷贝构造函数
    NoCopyCstor(const NoCopyCstor &){};
};

int main(){
    NoCopyCstor a;
    NoCopyCstor b(a);   // 无法通过编译
}

