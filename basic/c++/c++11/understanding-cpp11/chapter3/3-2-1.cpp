class Info {
public:
    Info() : type(1), name('a') { InitRest(); }
    Info(int i) : type(i), name('a') { InitRest(); }
    Info(char e): type(1), name(e) { InitRest(); }

private:
    void InitRest() { /* 其它初始化 */ }
    int  type;
    char name;
    // ...
};
