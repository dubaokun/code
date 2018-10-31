#include <stdint.h>
#include <iostream>

using std::cout;

enum TypeStatus {
    E_BASE = 0x00,
    E_UNSIGN,
    E_UNKNOWN
};

void Test(TypeStatus status)
{
    uint8_t u8 = 0;
    switch (status) {
        case E_BASE:
            for (int i = 0; i < 10; ++i) {
                u8 += 1;
                std::cout << u8 << std::endl;
            }        
            break;
        case E_UNSIGN:
            for (int i = 0; i < 10; ++i) {
                u8 += 1;
                std::cout << (unsigned)u8 << std::endl;
            }        
            break;
        default:
            std::cout << "default" << std::endl;
            break;
    }
    std::cout << "========================" << std::endl;
}       

template<typename T>
void TestTl(T t) {
    uint8_t u8 = 0;
    for (int i = 0; i < 10; ++i) {
        u8 += 1;
        std::cout << (typeof(t))u8 << std::endl; 
    }

    std::cout << "========================" << std::endl;
}

int main(int argc, char ** argv) {

    unsigned i = 0;
    TestTl(i);
    return 0;    

    Test(E_BASE);
    Test(E_UNSIGN);    
    Test(E_UNKNOWN);

    return 0;    

    uint8_t u8 = 0;

    for (int i = 0; i < 1200; ++i) {
        u8 += 1;
        std::cout << (unsigned)u8 << std::endl;
    }

    return 0;
}
