struct A {
    A (int a = 3, double = 2.4){}
};

struct B : A{
    using A::A;
};
