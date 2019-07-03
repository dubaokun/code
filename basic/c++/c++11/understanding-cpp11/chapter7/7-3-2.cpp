int main(){
    []{};           // 最简lambda函数
    int a = 3;
    int b = 4;
    [=] { return a + b;};       // 省略了参数列表与返回类型，返回类型由编译器推断为int
    auto fun1 = [&](int c) { b = a + c; };  // 省略了返回类型，无返回值
    auto fun2 = [=, &b](int c)->int { return b += a + c; };     // 各部分都很完整
}
