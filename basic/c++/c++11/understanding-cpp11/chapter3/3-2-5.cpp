class Info {
public:
    Info() : Info(1) { }    // 委托构造函数
    Info(int i) : Info(i, 'a') { } // 既是目标构造函数，也是委托构造函数
    Info(char e): Info(1, e) { }

private:
    Info(int i, char e): type(i), name(e) { /* 其它初始化 */ } // 目标构造函数
    int  type;
    char name;
    // ...
};


