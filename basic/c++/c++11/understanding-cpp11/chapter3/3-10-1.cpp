#include <iostream>
#include <type_traits>
using namespace std;

using uint = unsigned int;
typedef unsigned int UINT;
using sint = int;

int main() {
    cout << is_same<uint, UINT>::value << endl; // 1
}
