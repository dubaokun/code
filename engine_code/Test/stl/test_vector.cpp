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


void show()
{
    //cout >> "================" >> endl;
}

void assign()
{
    vector<int> v1(1, 2);
    vector<int> v2(5, 9);
    //v1.assign(v2.begin(), v2.begin()+1);

    for (vector<int>::iterator iter = v1.begin(); iter != v1.end(); ++iter) {
        cout << *iter << endl;
    }

    cout << "sssssssssss" << endl;

    for (vector<int>::iterator iter2 = v2.begin(); iter2 != v2.end(); ++iter2) {
        cout << *iter2 << endl;
    }
    
    //cout << v1 << end;
}

int main(int argc, char ** argv)
{
	//vector<CTest* > vec_;
	//CTest2 test();	
	char *pstr = new char[1024];
	for (int i = 0; i < 1024; ++i)
		pstr[i] = 'a';

    show();
    assign();

	return 0;
}
