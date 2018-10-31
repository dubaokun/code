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

static std::string a = "hello";
const std::string b = "world";

void foo(const std::string &str) {}

void test(IN const std::string& a, OUT std::string& b,
        std::string& c, std::string& d) {
    // std::string b = a;
    int aa = 1;
    const long &bb = (long)aa;
    std::string sa = "aaa";
    const std::string& sb = sa;
}

void test2() {
    using std::string;
    string a = "sas";
}

void test3(std::string * str) {
  *str = "abcdef";
}

int main() {
    std::cout << "hello !" << std::endl;
    foo(a + b);
    std::string str;
    test3(&str);
    std::cout << str << std::endl;
    return 0;
}

