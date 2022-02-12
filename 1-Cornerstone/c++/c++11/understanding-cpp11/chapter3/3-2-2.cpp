class Info {
public:
    Info() { InitRest(); }
    Info(int i) : type(i) { InitRest(); }
    Info(char e): name(e) { InitRest(); }

private:
    void InitRest() { /* 其它初始化 */ }
    int  type {1};
    char name {'a'};
    // ...
};
