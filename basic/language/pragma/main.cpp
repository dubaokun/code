#include <iostream>

using namespace std;

#pragma pack(16)
typedef struct
{
	long b;
    char buf[3];
    long a;
}kk;

#pragma pack()

int main(int argc, char ** argv)
{
	cout << sizeof(kk) << endl;
	cout << "sizeof(long)=" << sizeof(long) << endl;
	return 0;
}
