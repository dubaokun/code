/**********************************************************************************
 *	最上层的接口：c接口用于创建父类、销毁父类
 *  父类：用于c函数的调用创建与销毁
 *  子类：真正使用的
 *  调用完毕
 **********************************************************************************/

#ifndef _TESTSO_H_
#define _TESTSO_H_

#include "testinterface.h"

class CFather;								// 虚构了一个不存在的类，并且进行前置声明
class CSon : public CBase
{
public:
	CSon() {};
	~CSon() {};

public:
	virtual int add(void) {
		return -1;
	}
private:
	CFather* father_;						// 针对这个不存在的前置声明的类，进行成员变量的设置，定义为指针类型
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
