#include <iostream>
using namespace std;

template<typename T> void g(T* t) {}
template<typename T> void h(T t) {}

int main()
{
   g(nullptr);            // 编译失败, nullptr的类型是nullptr_t,而不是指针
   g((float*) nullptr);   // 推导出T = float

   h(0);                  // 推导出T = int
   h(nullptr);            // 推导出T = nullptr_t
   h((float*)nullptr);    // 推导出T = float*
}
