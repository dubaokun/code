/*
 * # Copyright (c) 2015 Bingchun Feng. All rights reserved.
 */

#include <iostream>
#include <string>

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

void foo(const std::string &str) {}
std::string a = "hello";
std::string b = "world";

void test(IN const std::string& a, OUT std::string& b) {
    //std::string b = a;
    int aa = 1;
    const long &bb = aa;
    std::string sa = "aaa";
    const std::string& sb = sa;
}

void test2() {
    using std::string;
    string a = "sas";

int main() {
    std::cout << "hello !" << std::endl;
    foo(a + b);
    return 0;
}

