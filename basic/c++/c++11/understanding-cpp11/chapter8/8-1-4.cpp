#include <iostream>
using namespace std;

class InComplete;
struct Completed{};

int main(){
    int a;
    long long b;
    auto & c = b;
    char d[1024];

    // 对内置类型和完整类型使用alignof
    cout << alignof(int) << endl        //  4
        << alignof(Completed) << endl;  //  1

    // 对变量,引用或者数组使用alignof
    cout << alignof(a) << endl          //  4
        << alignof(b) << endl           //  8
        << alignof(c) << endl           //  8，与b相同
        << alignof(d) << endl;          //  1, 与元素要求相同

    // 本句无法通过编译，Incomplete类型不完整
    // cout << alignof(Incomplete) << endl;
}
