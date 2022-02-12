#include <iostream>

enum IndexType
{
    INDEX_FULL = 0x1,
    INDEX_INC_NORMAL = 0x2,
    INDEX_INC_GOOD = 0x4,
    INDEX_FULL_CACHE = 0x8,
    INDEX_ALL = INDEX_FULL | INDEX_INC_NORMAL | INDEX_INC_GOOD
};

#define PRINTENUM(x) #x

int main(int argc, char ** argv) {
    IndexType a = INDEX_FULL;
    std::cout << PRINTENUM(IndexType::INDEX_FULL) << std::endl;
    return 0;
}
