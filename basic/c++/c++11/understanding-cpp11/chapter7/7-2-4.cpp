#include <type_traits>
#include <iostream>
using namespace std;

class NoCopyCstor {
public:
    NoCopyCstor() = default;

    // 使用 "= delete" 同样可以有效阻止用户
    // 错用拷贝构造函数
    NoCopyCstor(const NoCopyCstor &) = delete;
};

int main(){
    NoCopyCstor a;
    NoCopyCstor b(a);   // 无法通过编译
}
