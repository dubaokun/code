#include <cstdlib>
#include <iostream>
using namespace std;

typedef unsigned char uint8;
struct RGBA{
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
    
    RGBA(uint8 R, uint8 G, uint8 B, uint8 A = 0): 
        r(R), g(G), b(B), a(A){}
};

RGBA operator "" _C(const char* col, size_t n) {    // 一个长度为n的字符串col
    const char* p = col;
    const char* end = col + n;
    const char* r, *g, *b, *a;
    r = g = b = a = nullptr;

    for(; p != end; ++p) {
        if (*p == 'r') r = p;
        else if (*p == 'g') g = p;
        else if (*p == 'b') b = p;
        else if (*p == 'a') a = p;
    }

    if ((r == nullptr) || (g == nullptr) || (b == nullptr))
        throw;
    else if (a == nullptr)
        return RGBA(atoi(r+1), atoi(g+1), atoi(b+1));
    else
        return RGBA(atoi(r+1), atoi(g+1), atoi(b+1), atoi(b+1));
}

std::ostream & operator << (std::ostream & out, RGBA & col) {
    return out << "r: " << (int)col.r 
        << ", g: " << (int)col.g 
        << ", b: " << (int)col.b 
        << ", a: " << (int)col.a << endl;
}


void blend(RGBA && col1, RGBA && col2) {
    // Some color blending action
    cout << "blend " << endl << col1 << col2 << endl;
}

int main() {
    blend("r255 g240 b155"_C, "r15 g255 b10 a7"_C);
}
