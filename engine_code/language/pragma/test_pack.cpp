#include <iostream>

using namespace std;

#pragma pack(1)
typedef struct
{
	char a ;
    int b;
}A;
#pragma pack()

typedef struct
{
    char a;
    int b;
}B;

int main(int argc, char ** argv)
{
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	return 0;
}
