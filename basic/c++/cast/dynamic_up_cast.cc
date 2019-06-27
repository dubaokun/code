#include <iostream>
#include <iomanip>
using namespace std;

class Base{
public:
    Base(int a = 0): m_a(a){ }
    int get_a() const{ return m_a; }
    virtual void func() const { }

protected:
    int m_a;
};

class Derived: public Base{
public:
    Derived(int a = 0, int b = 0): Base(a), m_b(b){ }
    int get_b() const { return m_b; }

private:
    int m_b;
};

int main() {
    // ¿¿¿
    Derived *pd1 = new Derived(35, 78);
    Base *pb1 = dynamic_cast<Derived*>(pd1);
    cout<<"pd1 = "<<pd1<<", pb1 = "<<pb1<<endl;
    cout<<pb1->get_a()<<endl;
    pb1->func();

    // ¿¿¿
    int n = 100;
    Derived *pd2 = reinterpret_cast<Derived*>(&n);
    Base *pb2 = dynamic_cast<Base*>(pd2);
    cout<<"pd2 = "<<pd2<<", pb2 = "<<pb2<<endl;
    cout<<pb2->get_a()<<endl;  //Êä³öÒ»¸öÀ¬»øÖµ
    pb2->func();  //ÄÚ´æ´íÎó

    return 0;
}
