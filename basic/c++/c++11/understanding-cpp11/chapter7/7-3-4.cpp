int main() {
    int boys = 4, girls = 3;
    auto totalChild = [=]()->int{ return girls + boys; };   // 捕捉所有父作用域的变量
    return totalChild();
}
