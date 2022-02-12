#include <iostream>
#include <memory>
using namespace std;

struct ColorVector {
    double r;
    double g;
    double b;
    double a;
};

int main() {
    size_t const size = 100;
    ColorVector * const vec = new ColorVector[size];

    void* p = vec;
    size_t sz = size;

    void* aligned = align(alignof(double) * 4, size, p, sz);
    if (aligned != nullptr)
        cout << alignof(p) << endl;
}
