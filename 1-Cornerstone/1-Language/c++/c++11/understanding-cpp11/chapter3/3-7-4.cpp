#include <string>
using namespace std;

union T {
    string s;   // string有非平凡的构造函数
    int n;
};

int main() {
    T t;        // 构造失败，因为T的构造函数被删除了
}
