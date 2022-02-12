int main() {
    int girls = 3, boys = 4;
    auto totalChild = [](int x, int y)->int{ return x + y; };
    typedef int (*allChild)(int x, int y);
    typedef int (*oneChild)(int x);

    allChild p;
    p = totalChild;

    oneChild q;
    q = totalChild;     // 编译失败，参数必须一致

    decltype(totalChild) allPeople = totalChild;    // 需通过decltype获得lambdas的类型
    decltype(totalChild) totalPeople = p;           // 编译失败，指针无法转换为lambda
    return 0;
}
