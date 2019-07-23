#include <vector>
#include <iostream>

using namespace std;

class C3 {
 public:
    C3(){}
    C3(int ii,string ss):i(ii),s(ss){cout << " constructor " << endl;}
    C3(const C3& c):i(c.i+100),s(c.s + "hhhhhhhhhhh"){cout << " copy constructor " << endl;}
    C3(const C3&& c) {cout << "move constructor" << endl;}
	
	int i;
    string s;
};

int main(int argc, char ** argv) {
	vector <C3> vC;
    vC.reserve(10);
    // 传递的是右值，所以调用移动构造函数
    vC.push_back(C3(1,"ss"));
    cout << vC[0].i << endl;
    cout << endl;
    // 只有传递参数形式的构造函数的形式，才会直接调用一次构造函数
    vC.emplace_back(3,"kk");
    cout << vC[1].i << " " << vC[0].i << endl;

    cout << "======================" << endl;
    C3 c(4, "aa");
    // 传递非参数形式，并且传递的是右值，所以调用移动构造函数
    vC.emplace_back(std::move(c));
    cout << "======================" << endl;
    // 传递的是左值，所以调用拷贝构造函数
    vC.emplace_back(c);
    // 传递的是左值，所以调用拷贝构造函数
    vC.push_back(c);
}
