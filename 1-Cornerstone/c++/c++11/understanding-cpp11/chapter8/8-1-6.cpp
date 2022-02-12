#include <iostream>
using namespace std;

struct alignas(alignof(double)*4) ColorVector {
    double r;
    double g;
    double b;
    double a;
};

// 固定容量的模板数组
template <typename T>
class FixedCapacityArray {
public:
    void push_back(T t) { /* 在data中加入t变量 */}
    // ...
    // 一些其它成员函数，成员变量等
    // ...
    char alignas(T) data[1024] = {0};
    //int length = 1024 / sizeof(T);
};


int main() {
    FixedCapacityArray<char> arrCh;
    cout << "alignof(char): " << alignof(char) << endl;
    cout << "alignof(arrCh.data): " << alignof(arrCh.data) << endl;

    FixedCapacityArray<ColorVector> arrCV;
    cout << "alignof(ColorVector): " << alignof(ColorVector) << endl;
    cout << "alignof(arrCV.data): " << alignof(arrCV.data) << endl;
    return 1;
}
