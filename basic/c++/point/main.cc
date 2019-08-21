#include <iostream>

using namespace std;

class T {
 public:
    T() {cout << "构造T" << endl;}
    T(const T& t) {cout << "拷贝构造T" << endl;}
    
};

int test(const T& t) {
    T * tt = (T*)&t;

}

int main(int argc, char ** argv) {
    T * t = new T();
    test(*t);
    return 0;
} 
