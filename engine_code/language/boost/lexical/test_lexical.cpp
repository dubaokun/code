
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <string>
#include<vector>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

long getMilliTime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (static_cast<long>(t.tv_sec) * 1000ul
        + static_cast<long>(t.tv_usec) / 1000ul);
}

std::vector<std::string> splits;
std::vector<int> int_splits;
void init() {
    splits.clear();
    splits.reserve(1000000);
    int_splits.reserve(1000000);
    for (int i = 0; i < 1000000; i++) { 
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "%d", i);
        splits.push_back(buffer);
    }
    for (int i = 0; i < 1000000; i++) { 
        int_splits.push_back(i);
    }
}

void test_int() {
    cout <<  __FUNCTION__ << endl;
    
    long start1 = getMilliTime();
    for (int i = 0; i < splits.size(); i++) {
        int tmp = atoi(splits[i].c_str());
    }
    long end1 = getMilliTime();
    cout << "atoi cost:" << end1 - start1 << " ms\n";
    
    long start = getMilliTime();
    for (int i = 0; i < splits.size(); i++) {
        int tmp = boost::lexical_cast<int>(splits[i]);
    }
    long end = getMilliTime();
    cout << "boost::lexical_cast<int>  cost:" << end - start << " ms\n";
}
void test_string() {
    cout << endl <<   __FUNCTION__ << endl;
    
    long start1 = getMilliTime();
    char buffer[128];
    for (int i = 0; i < int_splits.size(); i++) {
        snprintf(buffer, sizeof(buffer), "%d", int_splits[i]);
        string tmp = buffer;
    }
    long end1 = getMilliTime();
    cout << "atoi cost:" << end1 - start1 << " ms\n";
    
    long start = getMilliTime();
    for (int i = 0; i < int_splits.size(); i++) {
        string tmp = boost::lexical_cast<string>(splits[i]);
    }
    long end = getMilliTime();
    cout << "boost::lexical_cast<string>  cost:" << end - start << " ms\n";
}
int main()
{
    init();
    test_int();
    test_string();
    return 0;

}
