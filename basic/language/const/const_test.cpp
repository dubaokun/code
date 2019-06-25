#include <iostream>

struct A {
    int a;
    int b;
};

void show(const A& a) {
    std::cout << a.a << std::endl;
    std::cout << a.b << std::endl;
}

int main(int argc, char ** argv) {
    int a = 0;
    const int * p = &a;
    std::cout << *p << std::endl; 

    std::cout << "========================" << std::endl;

    A a_;
    a_.a = 0;
    a_.b = 1;

    show(a_);
    const A * b_ = &a_;
    b_->a = 10;
    b_->b = 11;
    show(*b_);

    return 0;
}
