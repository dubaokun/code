#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp>

class implementation
{
public:
    ~implementation() { std::cout <<"destroying implementation\n"; }
    void do_something() { std::cout << "did something\n"; }
};

void test()
{
    boost::shared_ptr<implementation> sp1(new implementation());
    std::cout<<"The Sample now has "<<sp1.use_count()<<" references\n";

    boost::shared_ptr<implementation> sp2 = sp1;
    std::cout<<"The Sample now has "<<sp2.use_count()<<" references\n";
    
    sp1.reset();
    std::cout<<"After Reset sp1. The Sample now has "<<sp2.use_count()<<" references\n";
    
    implementation* t = sp2.get();
    t->do_something();
    sp2->do_something();

    sp2.reset();
    std::cout<<"After Reset sp2.\n";
}

int main(int argc, char ** argv)
{
    test();

    return 0;
}

