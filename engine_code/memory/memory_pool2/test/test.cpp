#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

void test()
{
	char a[20] = {0};
	for (int i = 0; i < 20; ++i) {
		a[i] = 'a';
	}

	/*char ** p = &((char *)a);
	cout << a << endl;	
	*((int *)a) = 1;
	cout << a << endl;
	cout << *((int *)a) << endl;
	cout << a + sizeof(int) << endl;
	cout << *p - sizeof(int) << endl;
	*/
}

void test2()
{
	vector<void *> vec;
	vec.resize(3);
	void * pstr = new char[10];
	char * p = (char *)pstr;
	for(int i = 0; i < 10; ++i) {
		p[i] = 'a';
	}
	
	cout << pstr << endl;
	printf("%p\n", pstr);
	printf("%p\n", &p[0]);
	cout << p << endl;
	memset(pstr, 0x00, 10);
	cout << "======" << endl;
	cout << p << endl;
	vec.push_back(p);

	cout << "===========================" << endl;
	cout << sizeof(void *) << endl;
	vec.push_back(p);
	cout << vec.size() << endl;
}

int main(int argc, char ** argv)
{
	test2();
	return 0;

	test();
	return 0;
	unsigned int size = 128;
	double factor = 1.06;
	for(int i = 1; i < 64; ++i)
	{
		size *= factor;
		cout << size << endl;
	}
	return 0;
}
