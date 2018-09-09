#include <vector>
#include <iostream>

using namespace std;

class CTest
{
	public:
		CTest() {};
		~CTest() {};

	private:
		int a;
		int b;
};

class CTest2 
{
	public:
		CTest2() {};
		~CTest2() {};

	private:
		vector<CTest*> vec_;
};

int main(int argc, char ** argv)
{
	//vector<CTest* > vec_;
	//CTest2 test();	
	char *pstr = new char[1024];
	for (int i = 0; i < 1024; ++i)
		pstr[i] = 'a';
	return 0;
}
