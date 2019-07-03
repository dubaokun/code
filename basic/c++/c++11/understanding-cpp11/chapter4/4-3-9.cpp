int i;
decltype(i) a;      // a: int
decltype((i)) b;    // b: int &, 无法编译通过
