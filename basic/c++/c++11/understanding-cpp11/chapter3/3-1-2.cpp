struct A { 
    A(int i) {}
    A(double d, int i) {}
    A(float f, int i, const char* c) {}
    // ...
};

struct B : A { 
    B(int i): A(i) {} 
    B(double d, int i) : A(d, i) {}
    B(float f, int i, const char* c) : A(f, i, c){}
    // ...
    virtual void ExtraInterface(){}
};

