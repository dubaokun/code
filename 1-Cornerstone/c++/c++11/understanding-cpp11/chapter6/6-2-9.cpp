#include <iostream>
#include <tuple>
using namespace std;

template <typename... T> void PrintVarTemp(T...args) {
    auto params = make_tuple(args...);

    int i;
    for (i = 0; i < sizeof...(args); ++i){
        cout << get<i>(params) << endl;  // 无法通过编译，i是运行时的变量
    }

    for (auto j : params) {     // 无法通过编译，params不是一个同种类型的container
        cout << j << endl;
    }
}

int main() {
    PrintVarTemp("There are totally ", 11 + 23 * 4 + 35 ," boy", 's', "\n");
    return 0;
}
