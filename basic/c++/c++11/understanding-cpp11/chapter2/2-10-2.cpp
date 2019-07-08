#include <iostream>


struct Object{
    virtual void fun() = 0;
};

struct Base : public Object {
    void fun() {}   // 声明为final
};

struct Derived : public Base {
    void fun(int a) {std::cout << "a" << std::endl;}     // 无法通过编译
};

int main(int argc, char** argv) {
	Derived derive;
	derive.fun(1);
	return 0;
}
