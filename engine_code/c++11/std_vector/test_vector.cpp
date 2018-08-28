#include <vector>
#include <iostream>

using namespace std;

void test1()
{
	vector<int> _vec(100);
	cout << "vector size = " << _vec.size() << endl;	
}

int main(int argc, char ** argv)
{
	test1();
	return 0;
}
