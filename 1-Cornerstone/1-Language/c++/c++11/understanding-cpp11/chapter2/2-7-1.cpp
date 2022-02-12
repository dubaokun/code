class Init{
public:
    Init(): a(0){}
    Init(int d): a(d){}

private:
    int a;
    const static int b = 0;
    int c = 1;          // 成员，无法通过编译
    static int d = 0;   // 成员，无法通过编译
    static const double e = 1.3;        // 非整型或者枚举，无法通过编译
    static const char * const f = "e";  // 非整型或者枚举，无法通过编译
};
