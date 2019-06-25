#include <iostream>
#include <typeinfo>

using namespace std;

int main(int argc, char ** argv)
{
	int b = 5, c = 2;
	float a = b / c;
	cout << typeid(a).name() << endl;
	cout << a << endl;
	cout << "==========" << endl;
	float e = (float) b / c;
	cout << e << endl; 
	return 0;
}
