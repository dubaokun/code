#include "testso.h"

int A::add(void)
{
    return a + b;
}

extern "C"
{
    CBase* create(void)				// 注意：create函数必须返回Base的对象，不能直接返回A的对象，否则后面调用A::add()的时候会提示错误。
    {
        return new A;
    }

    void destory(CBase *p)
    {
        if (p) delete p;
    }
}
