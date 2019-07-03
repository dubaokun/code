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

std::ostream & operator << (std::ostream & out, RGBA & col) {
    return out << "r: " << (int)col.r 
        << ", g: " << (int)col.g 
        << ", b: " << (int)col.b 
        << ", a: " << (int)col.a << endl;
}

void blend(RGBA & col1, RGBA & col2){
    cout << "blend " << endl << col1 << col2 << endl;
}

int main() {
    RGBA col1(255, 240, 155);
    RGBA col2({15, 255, 10, 7});  // C++11风格的列表初始化
    blend(col1, col2);
}
