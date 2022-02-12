void DoSomething1();
void DoSomething2();

[[ noreturn ]] void ThrowAway() {
    throw "expection"; // 控制流跳转到异常处理
}

void Func(){
    DoSomething1();
    ThrowAway();
    DoSomething2(); // 该函数不可到达
}
