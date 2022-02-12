#include <type_traits>
#include <iostream>
using namespace std;

class TwoCstor {
public:
    // 提供了带参数版本的构造函数，则必须自行提供
    // 不带参数版本，且本class不再是POD类型
    TwoCstor() {};
    TwoCstor(int i): data(i) {}

private:
    int data;
};

int main(){
    cout << is_pod<TwoCstor>::value << endl;
}
