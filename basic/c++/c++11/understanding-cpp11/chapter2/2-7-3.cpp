#include <iostream>
using namespace std;

struct Mem {
    Mem() { cout << "Mem default, num: " << num << endl; }
    Mem(int i): num(i) { cout << "Mem, num: " << num << endl; }

    int num = 2;  // 使用"="初始化非静态成员
};

class Group {
public:
    Group() { cout << "Group default. val: " << val << endl; }
    Group(int i): val('G'), a(i) { cout << "Group. val: " << val << endl; }
    void NumOfA() { cout << "number of A: " << a.num << endl; }
    void NumOfB() { cout << "number of B: " << b.num << endl; }

private:
    char val{'g'};  // "{}"初始化非静态成员
    Mem a;
    Mem b{19};      // "{}"初始化非静态成员
};

int main() {
    Mem member;         // Mem default, num: 2

    Group group;        // Mem default, num: 2
                        // Mem, num: 19
                        // Group default. val: g

    group.NumOfA();     // number of A: 2
    group.NumOfB();     // number of B: 19

    Group group2(7);    // Mem, num: 7
                        // Mem, num: 19
                        // Group. val: G

    group2.NumOfA();    // number of A: 7
    group2.NumOfB();    // number of B: 19
}
