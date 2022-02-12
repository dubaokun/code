#include <iostream>
using namespace std;

[[ noreturn ]] void Func(int i){ 
    //当参数i的值为0时，该函数行为不可估计！
    if (i < 0)
        throw "negative";
    else if (i > 0)
        throw "positive";
}

int main(){
    Func(0);
    cout << "Returned" << endl; // 无法执行该句
    return 1;
}
