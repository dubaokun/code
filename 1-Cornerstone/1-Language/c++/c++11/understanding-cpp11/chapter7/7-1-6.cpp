#include <cstdio>
#include <cstddef>
using namespace std;

int main(){
    nullptr_t my_null;
    printf("%x\n", &my_null);

    // printf("%x", &nullptr);      // 根据C++11的标准设定，本句无法编译通过
    printf("%d\n", my_null == nullptr);

    const nullptr_t && default_nullptr = nullptr;    // default_nullptr是nullptr的一个右值引用
    printf("%x\n", &default_nullptr);
}

