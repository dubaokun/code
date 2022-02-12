#include <iostream>
using namespace std;

struct A {
    ~A() { throw 1; }
};

struct B {
    ~B() noexcept(false) { throw 2; }
};

struct C {
    B b;
};

int funA() { A a; }
int funB() { B b; }
int funC() { C c; }


int main() {
    try {
        funB();
    }
    catch(...){
        cout << "caught funB." << endl; // caught funB.
    }

    try {
        funC();
    }
    catch(...){
        cout << "caught funC." << endl; // caught funC.
    }

    try {
        funA(); // terminate called after throwing an instance of 'int'
    }
    catch(...){
        cout << "caught funA." << endl;
    }
}
