template <typename T> class X {};
template <typename T> void TempFun(T t){};
struct A{} a;
struct {int i;}b;           // b是匿名类型变量
typedef struct {int i;}B;   // B是匿名类型

void Fun()
{
    struct C {} c;          // C是局部类型

    X<A> x1;    // C++98 - 通过，C++11 - 通过
    X<B> x2;    // C++98 - 错误，C++11 - 通过
    X<C> x3;    // C++98 - 错误，C++11 - 通过
    TempFun(a); // C++98 - 通过，C++11 - 通过
    TempFun(b); // C++98 - 错误，C++11 - 通过
    TempFun(c); // C++98 - 错误，C++11 - 通过
}
