#include <string>
#include <iostream>

// lambda expression with no parameters
auto basicLambda = [] { std::cout << "lambda test" << std::endl;};
// lambda expression with parameters
auto basicLambda1 = [](std::string str) { std::cout << "lambda test=" << str << std::endl; };
// function point
void fileFuck() {
    std::cout << "function point!" << std::endl;
}

void Test1() {
    // lambda expression with no parameters 
    basicLambda();
    // lambda expression with parameters
    basicLambda1("basicLambda1");
    // function point
    void (*funcp) ();       // function point declaration
    funcp = fileFuck;       // function point define
    (*funcp)();             // funttion call
}

int main(int argc, char** argv) {
    Test1();
    return 0;
}
