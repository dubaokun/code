struct A { 
    A(int i) {}
    A(double d, int i) {}
    A(float f, int i, const char* c) {}
    // ...
};

struct B : A { 
    using A::A;     // 继承构造函数
    // ...
    virtual void ExtraInterface(){}
};

