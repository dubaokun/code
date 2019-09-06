#include <iostream>

using namespace std;

int test() {
    cout << "1111111111111" << endl;
}

int main(int argc, char ** argv) {
    int a = 0;
    if (0 != a && test())
    {
		cout << "a!=0" << endl;
    }
    return 0;
}
