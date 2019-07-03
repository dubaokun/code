#include <string>
struct init{ int a = 1; double b {1.2}; static constexpr int c = 0; std::string d {"helll"};};
#if 0
class B{
    B(int i): a(i){}
    int a;
};

struct init{ int a = 1; std::string b{"hello"}; B b{1};};
#endif
