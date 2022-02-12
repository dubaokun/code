int main() {
    int *p = new int;
    int *q = (int*)(reinterpret_cast<long long>(p) ^ 2012);   // q隐藏了p

    // 做一些其它工作，垃圾回收器可能已经回收了p指向对象
    q = (int*)(reinterpret_cast<long long>(q) ^ 2012);    // 这里的q == p
    *q = 10;
}
