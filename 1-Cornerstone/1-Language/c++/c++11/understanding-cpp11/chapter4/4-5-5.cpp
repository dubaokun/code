#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    for (auto i = v.begin(); i != v.end(); ++i)
        cout << *i << endl;     // i是迭代器对象

    for (auto e: v)
        cout << e << endl;      // e是解引用后的对象
}
