template <int i> class X{};
template <class T> class Y{};

Y<X<1> > x1;    // 编译成功
Y<X<2>> x2;     // 编译失败
