/*  
 *  Author : 
 *      Sam, 2018-11-02 
 *
 *
 *  Brief:
 *      1.parameters; 2.return value; 3.function body  
 *
 */

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

void Test2() {
    int x = 10;

    auto add_x = [x](int a) { return a + x; }; 
    auto multiply_x = [&x](int a) { return a * x; }; 

    std::cout << add_x(10) << " " << multiply_x(10) << std::endl;
}

void Test3() {
    []() {std::cout <<  "立即执行！" << std::endl;};
}

int main(int argc, char** argv) {
    Test1();
    Test2();
    std::cout << "==============================" << std::endl;
    Test3();
    return 0;
}
