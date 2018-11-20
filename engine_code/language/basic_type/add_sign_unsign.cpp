#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
    unsigned int x = 9;
    int y = -20;
    int m = (x + y > 9) ? 1 : 0;
    int z = x + y;

    cout << x + y << endl; 
    cout<<"z is "<< z <<endl;
    cout<<"m is "<< m <<endl;
    
    return 0;
}
