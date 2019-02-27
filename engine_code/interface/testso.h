/**********************************************************************************
 *	最上层的接口：c接口用于创建父类、销毁父类
 *  父类：用于c函数的调用创建与销毁
 *  子类：真正使用的
 *  调用完毕
 **********************************************************************************/

#ifndef _TESTSO_H_
#define _TESTSO_H_

#include "testinterface.h"

class CSon : public CBase
{
public:
	CSon() {};
	~CSon() {};

public:
	virtual int add(void) {
		return -1;
	}
};

class CGrandSon : public CSon
{
public:
	CGrandSon() {};
	~CGrandSon() {};

public:
    int c;

public:
    virtual int add(void);
};


#endif // _TESTSO_H_
