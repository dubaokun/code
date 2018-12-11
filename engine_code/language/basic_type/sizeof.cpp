#include <stdint.h>
#include <iostream>

using namespace std;

#pragma pack(1)
struct P13nItemUnit {
    int64_t skuid_;
    float score_;
};
#pragma pack()

struct P13nItemUnit2 {
    int64_t skuid_;
    float score_;
};

int main(int argc, char ** argv) {
    cout << sizeof(int64_t) << endl;
    cout << sizeof(float) << endl;
    cout << sizeof(P13nItemUnit) << endl;
    cout << sizeof(P13nItemUnit2) << endl;
    return 0;
}
