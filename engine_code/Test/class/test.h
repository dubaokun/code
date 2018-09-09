#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>

class CTest
{
public:
    static bool create();
    void load();
    void out();

private:
    CTest();
    ~CTest();

private:
    static CTest * _inst_1;
    static CTest * _inst_2;

    char * _pstr;
};


#endif
