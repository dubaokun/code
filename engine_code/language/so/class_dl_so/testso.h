/**********************************************************************************
 *	最上层的接口：c接口用于创建父类、销毁父类
 *  父类：用于c函数的调用创建与销毁
 *  子类：真正使用的
 *  调用完毕
 **********************************************************************************/

#ifndef _TESTSO_H_
#define _TESTSO_H_

// 只能通过基类调用，因此需要先定义一个基类，然后在create中生成真正需要生成的对象。

class CBase{
public:
	CBase() {};
	~CBase() {};

public:
    int a, b;
    virtual int add(void) = 0;
};

class Base : public CBase
{
public:
	Base() {};
	~Base() {};

public:
	virtual int add(void) {
		return -1;
	}
};

class A : public Base
{
public:
	A() {};
	~A() {};

public:
    int c;

public:
    int add(void);
};

typedef CBase* create_t(void);					// create factory
typedef void destory_t(CBase*);					// destory

#endif // _TESTSO_H_
