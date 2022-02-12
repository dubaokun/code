#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	void * pstr = new char[10];
	cout << pstr << endl;
	void * p = pstr;
	char a = 'a';
	for(int i = 0; i < 10; ++i) {
		*((char *) p) = a;
		a = a + 1;
		p = (char *)p +1;
	}

	cout << (char *)pstr << endl;

	return 0;

}
