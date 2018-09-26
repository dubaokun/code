#include <stdint.h>
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
    
    cout << "========================" << endl;
    uint64_t max_size = 100;//G
    max_size = max_size << 30;
    cout << max_size << endl;
    cout << "========================" << endl;

    cout << "========================" << endl;
    int max_size2 = 100;//G
    uint64_t max_size3 = (uint64_t)max_size2 << 30;
    cout << max_size3 << endl;
    cout << "========================" << endl;


    return 0;
}
