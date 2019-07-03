#include <iostream>
#include <vector>
using namespace std;

class Mydata {
public:
    Mydata & operator [] (initializer_list<int> l)
    {
        for (auto i = l.begin(); i != l.end(); ++i)
            idx.push_back(*i);
        return *this;
    }
    Mydata & operator = (int v) 
    {
        if (idx.empty() != true) {
            for (auto i = idx.begin(); i != idx.end(); ++i) {
                d.resize((*i > d.size()) ? *i : d.size());
                d[*i - 1] = v;
            }
            idx.clear();
        }
        return *this;
    }

    void Print() {
        for (auto i = d.begin(); i != d.end(); ++i) 
            cout << *i << " ";
        cout << endl;
    }

private:
    vector<int> idx;    // 辅助数组，用于记录index
    vector<int> d;
};

int main() {
    Mydata d;
    d[{2, 3, 5}] = 7;
    d[{1, 4, 5, 8}] = 4;
    d.Print();  // 4 7 7 4 4 0 0 4
}
