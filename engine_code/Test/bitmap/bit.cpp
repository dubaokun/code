#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
    int pos = 1;
    pos <<= 1;

    int pos2 = 1 << 1;
    pos2 <<= 1;

    cout << pos << endl;
    cout << pos2 << endl;
    return 0;
}
