#include <iostream>
#include <vector>

using namespace std;

void Test1()
{
    int a = 0;
    if (0 == a){
        a = 1;
        cout << "a=0" << endl;
    } else if (1 == a) {
        a = 2;
        cout << "a=1" << endl;
    } else {
        cout << "a=2" << endl;
    }

}

void Test2()
{
    int a = 100;
    if (a > 0) {
        cout << "a > 0" << endl;
    } else if (a > 10) {
        cout << "a > 10" << endl;
    } else {
        cout << "a = 100" << endl;
    }
    
    return;
} 

void Test3() {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    if (not vec.empty()) {
        cout << "vec not empty!" << endl;
    }
}

int main(int argc, char ** argv)
{
    Test2();
    Test3();
    return 0;
}
