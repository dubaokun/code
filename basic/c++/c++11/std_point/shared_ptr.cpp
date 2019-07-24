#include <memory>
#include <utility>
#include <iostream>
#include <unistd.h>

class A {
 public:
    A() { std::cout << "A gouzao" << std::endl;}
    ~A() {std::cout << "A xigou" << std::endl;}
};

int main()
{
    std::shared_ptr<A> aa = nullptr;
    if (!aa) {
        std::cout << "aa nullptr!" << std::endl;
    }

    std::cout << "===============================" << std::endl;
   
	std::shared_ptr<A> a = std::make_shared<A>();
    a = std::make_shared<A>();

	while(1)
    {
		sleep(1);
	}

	int *p = new int(30);
    std::shared_ptr<int> bptr(p);//方式1
    std::shared_ptr<int> aptr = std::make_shared<int>(20);//方式
    std::shared_ptr<int> cptr(aptr);
    std::cout << "aptr.use_count() = " << aptr.use_count() <<"  value = "<<*aptr<<std::endl;//use_count 是引用计数器
    std::cout << "bptr.use_count() = " << bptr.use_count() <<"  value = "<<*bptr<<std::endl;
    std::cout << "cptr.use_count() = " << cptr.use_count() <<"  value = "<<*cptr<<std::endl;
}
