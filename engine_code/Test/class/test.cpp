#include "test.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

CTest * CTest::_inst_1 = NULL;
CTest * CTest::_inst_2 = NULL;

CTest::CTest()
{
    _pstr = NULL;
}

CTest::~CTest()
{
    if (NULL != _pstr) {
        delete _pstr;
        _pstr = NULL;
    }
}

bool CTest::create()
{
    if (NULL !=_inst_1 || NULL != _inst_2) return false;

    _inst_1 = new CTest;
    _inst_2 = new CTest;

    _inst_1->load();
    _inst_2->load();

    return true;
}

void CTest::load()
{
    std::cout << "load" << std::endl;
    if (NULL == _pstr) {
        std::cout << "NULL == _pstr" << std::endl;
        _pstr = new char[1024];
        memset(_pstr, 0x00, 1024);
        sprintf(_pstr, "%s", "hello word");
    }
}

void CTest::out()
{
    std::cout << _pstr << std::endl;
}

