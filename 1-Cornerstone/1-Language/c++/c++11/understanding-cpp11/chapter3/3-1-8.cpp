struct A { A (int){} };
struct B : A{ using A::A; };

B b;    // B没有默认构造函数

