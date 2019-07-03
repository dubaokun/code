struct Object{
    virtual void fun() = 0;
};

struct Base : public Object {
    void fun() final;   // 声明为final
};

struct Derived : public Base {
    void fun();     // 无法通过编译
};
