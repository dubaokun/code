struct MyType {
    constexpr MyType(int x): i(x){}
    int i; 
};
constexpr MyType mt = {0};

