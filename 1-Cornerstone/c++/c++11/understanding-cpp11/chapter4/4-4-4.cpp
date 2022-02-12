#include <iostream>
using namespace std;

double foo(int a) {
    return (double)a + 0.1;
}

int foo(double b) {
    return (int)b;
}

template <class T> 
auto Forward(T t) -> decltype(foo(t)){
    return foo(t);
}

int main(){
    cout << Forward(2) << endl;     // 2.1
    cout << Forward(0.5) << endl;   // 0
}
