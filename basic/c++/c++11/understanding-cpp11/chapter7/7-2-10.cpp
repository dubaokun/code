#include <cstddef>
#include <new>

extern void* p;

class NoStackAlloc{
public:
    ~NoStackAlloc() = delete;
};

int main(){
    NoStackAlloc nsa;   // 无法通过编译
    new (p) NoStackAlloc(); // placement new, 假设无需析构
    return 1;
}
