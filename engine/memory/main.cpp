#include <iostream>

using namespace std;

char * g_str = NULL;

void get(char *& pstr)
{
	pstr = g_str;
	g_str = NULL;
}

int main(int argc, char ** argv)
{
	char * pstr = NULL;
	g_str = new char[100];
	for (int i = 0; i < 100; ++i) {
		g_str[i] = 'b';
	}

	get(pstr);
		
	cout << pstr << endl;		
}
