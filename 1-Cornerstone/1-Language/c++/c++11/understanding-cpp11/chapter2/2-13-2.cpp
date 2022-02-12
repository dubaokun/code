template <typename T> struct MyTemplate { };

int main() { 
    //MyTemplate<struct { int a; }> t; // 无法编译通过, 匿名类型的声明不能在模板实参位置
    MyTemplate<decltype({struct { int a; }s;})> t; // 无法编译通过, 匿名类型的声明不能在模板实参位置
    return 0;
}
