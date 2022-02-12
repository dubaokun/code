#include <iostream>
using namespace std;

struct People {
public:
    int hand;
    static People * all;
};

int main() {
    People p;
    cout << sizeof(p.hand) << endl;         // C++98 中通过, C++11 中通过
    cout << sizeof(People::all) << endl;    // C++98 中通过, C++11 中通过
    cout << sizeof(People::hand) << endl;   // C++98 中错误, C++11 中通过
}
