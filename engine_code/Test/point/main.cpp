#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	void * p1 = NULL;
	char * p2 = NULL;
	int * p3 = NULL;
	cout << "void *=" << sizeof(p1) << " char *=" << sizeof(p2) << " int*=" << sizeof(p3) << endl;
	return 0;
}
