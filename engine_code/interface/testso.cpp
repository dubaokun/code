#include "testso.h"

int CGrandSon::add(void)
{
    return a + b;
}

extern "C"
{
    CBase* create(void)				// 注意：create函数必须返回Base的对象，不能直接返回CGrandSon的对象，否则后面调用CGrandSon::add()的时候会提示错误。
    {
        return new CGrandSon;
    }

    void destory(CBase *p)
    {
        if (p) delete p;
    }
}
