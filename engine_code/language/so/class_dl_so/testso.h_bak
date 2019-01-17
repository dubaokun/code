#ifndef _TESTSO_H_
#define _TESTSO_H_

// 只能通过基类调用，因此需要先定义一个基类，然后在create中生成真正需要生成的对象。

class CBase{
};

class Base : public CBase
{
public:
    int a, b;

    virtual int add(void) = 0;
//    {
//      return -1;
//    }
};

class A : public Base
{
public:
    int c;
public:
    int add(void);
};

//extern "C" 
//{
 //       Base* create(void);
   //     void destroy(Base *p);

        typedef Base* create_t(void);  // create factory
        typedef void destory_t(Base*); // destory
//}

#endif // _TESTSO_H_
