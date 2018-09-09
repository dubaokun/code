#include<iostream>

using namespace std;

int main()
{
	unsigned int x=9;
	int y=-20;
	int m=(x+y>9)?1:0;
	int z=x+y;
	
	long s_a = -1;
	cout << "s_a" << s_a << endl;
	if (s_a > x)
		cout << "s_a > x" << endl;
	else
		cout << "s_a < x" << endl;

	if(x > y)
		cout << "x > y" << endl;
	else
		cout << "x < y" << endl;

	cout<<x+y<<endl; 
	cout<<"m is "<<m<<endl;
  	cout<<"z is "<<z<<endl;
	return 0;
}
