#include <iostream>
#include <vector>
#include <boost/noncopyable.hpp>
class A : boost::noncopyable
{
    public:
        //A();
        //A(A&&a):a_(std::move(a.getValue())){}
        A& operator = (A&&) {}
        explicit A(int a):a_(a){}
        int getValue(){return a_;}
    private:
        int a_;
};

int main()
{
    std::vector< A > myVec;
    myVec.reserve(10);
    for(int i=0;i<10;++i)
    {
        A a(i);
        myVec.push_back(std::move(a));//std::move
    }

    for(int i=0;i<10;++i)
    {
        std::cout<<myVec[i].getValue()<<std::endl;
    }
    return 0;
}
