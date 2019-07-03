struct Test {
    typedef int foo;
};
 
template <typename T> 
void f(typename T::foo) {}  // 第一个模板定义 - #1
 
template <typename T> 
void f(T) {}                // 第二个模板定义 - #2
 
int main() {
    f<Test>(10);    // 调用#1.
    f<int>(10);     // 调用#2. 由于SFINEA，虽然不存在类型int::foo)，也不会发生编译错误
}
