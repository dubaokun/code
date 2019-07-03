#include <memory>
#include <iostream>
using namespace std;

void Check(weak_ptr<int> & wp) {
    shared_ptr<int> sp = wp.lock(); // 转换为shared_ptr<int>
    if (sp != nullptr)
        cout << "still " << *sp << endl;
    else
        cout << "pointer is invalid." << endl;
}

int main() {
    shared_ptr<int> sp1(new int(22));
    shared_ptr<int> sp2 = sp1;
    weak_ptr<int> wp = sp1; // 指向shared_ptr<int>所指对象

    cout << *sp1 << endl;   // 22
    cout << *sp2 << endl;   // 22
    Check(wp);              // still 22

    sp1.reset();
    cout << *sp2 << endl;   // 22
    Check(wp);              // still 22

    sp2.reset();
    Check(wp);              // pointer is invalid
}
