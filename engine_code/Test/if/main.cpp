#include <iostream>

using namespace std;

int main(int argc, char ** argv)
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
    return 0;
}
