#include <iostream>
#include <algorithm>

using namespace std;

bool test_lower_bound(int value)
{
    int * begin = new int[100];
    int * end = &begin[99];
    for (int i = 0; i < 100; ++i) {
        begin[i] = i;
    }

    int * p = std::lower_bound(begin, end, value);
    if (p == end) {
        cout << "not find" << endl;
        return false;
    }

    cout << *p << endl;
    
    return true; 
}

bool test_upper_bound(int value)
{
    int * begin = new int[100];
    int * end = &begin[99];
    for (int i = 0; i < 100; ++i) {
        begin[i] = i;
    }

    int * p = std::upper_bound(begin, end, value);
    if (p == end) {
        cout << "not find" << endl;
        return false;
    }

    cout << *p << endl;
    
    return true; 
}

int main(int argc, char ** argv)
{
    if (2 != argc) {
        cout << "less param" << endl;
    }

    int value = atoi(argv[1]);
    
    cout << "value=" << value << endl;

    cout << "test_lower_bound" << endl;
    test_lower_bound(value); 

    cout << "test_upper_bound" << endl;
    test_upper_bound(value);
        
    return 0;
}
