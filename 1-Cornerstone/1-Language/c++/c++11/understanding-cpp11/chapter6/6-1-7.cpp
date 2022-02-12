#include <iostream>
using namespace std;

constexpr int Fibonacci(int n) {
    return (n == 1) ? 1 : ((n == 2) ? 1 : Fibonacci(n - 1) + Fibonacci(n - 2));
}

int main() {
    int fib[] = { 
        Fibonacci(11), Fibonacci(12), 
        Fibonacci(13), Fibonacci(14), 
        Fibonacci(15), Fibonacci(16) 
    };

    for (int i : fib) cout << i << endl;
}

