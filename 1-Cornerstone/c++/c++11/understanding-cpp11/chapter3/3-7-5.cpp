#include <string>
using namespace std;

union T {
    string s; 
    int n;
public:
    // 自定义构造函数和析构函数
    T(){ new (&s) string; }
    ~T() { s.~string(); }
};

int main() {
    T t;        // 构造析构成功
}
