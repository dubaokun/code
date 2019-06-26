#include <stdio.h>
#include <unistd.h>
#include <iostream>
 
class A
{
public:
	A() { std::cout << "A Constructor" << std::endl; }
	A(const A&) { std::cout << "A Copy Constructor" << std::endl; }
	A &operator=(const A&) { std::cout << "A operator = " << std::endl; }
	~A() {std::cout << "A Destructor" << std::endl;}
};

class B
{
public:
	B() { std::cout << "B Constructor" << std::endl; }
	B(const B&) { std::cout << "B Copy Constructor" << std::endl; }
	~B() {std::cout << "B Destructor" << std::endl;}
};
 
A getA(A ta, B tb)
{
	std::cout << "====-2" << std::endl;
	A a1; //-----A Constructor
	std::cout << "====-3" << std::endl;
	return a1;//-----A Copy Constructor temp=a1, A Destructor a1
}
 
int main()
{
	A a; //----A Constructor
	B b; //----B Constructor
	std::cout << "====-1" << std::endl;
	A a2 = getA(a,b);   //---- B Copy Constructor, A Copy Constructor.......(a2=temp) A Copy Constructor.....A Destructor(temp des)
 
    return 0;
  
	A a3;//如果此处先定义了a2,然后再进行a2对象的再次赋值，会发生什么？？？？而不是像上面那种直接进行定义赋值。结果见下面3图
 
	a3 = getA(a,b);
 
	std::cout << "====-1" << std::endl;
	return 0;
}
