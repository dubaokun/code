#include <iostream>
#include <string>

using std::string;

class CTest {
public:
    CTest(int i){};
    ~CTest(){};

public:
    bool set_str(string& str) { str_test_ = str; };
    const string& get_str() const {return  str_test_; };

private:
    string str_test_; 
};


int main(int argc, char **argv)
{
    CTest t1(1);
    string str("aaabbbccc");
    t1.set_str(str);
    std::cout << t1.get_str() << std::endl;
    return 0;
}
