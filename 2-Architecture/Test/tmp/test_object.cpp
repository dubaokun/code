#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

class Test {
public:
	Test(){};
	~Test(){};

	int read(int fd, void * buf, size_t count); 
	void woca();
	void woca2();
	
};



int Test::read(int fd, void * buf, size_t count) {
	cout << "self" << endl;
}

void Test::woca() {
	int fd = open("./dTesttTest", O_RDONLY);
	char buffer[1024] = {0};
	int count = 10;
	read(fd, buffer, count);
	cout << buffer << endl;	
}

void Test::woca2() {
	int fd = open("./data", O_RDONLY);
	char buffer[1024] = {0};
	int count = 10;
	::read(fd, buffer, count);
	cout << buffer << endl;	
}


int main(int argc, char ** argv)
{
	Test* t1 = new Test();
	t1->woca();
	t1->woca2();
}
