#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define ALIGND8BYTES(x) (((x)+7L)&(~7L))

int main(int argc, char ** argv)
{
	int len = 100 + sizeof(char *);
	int tmp = ALIGND8BYTES(len);

	int size = sizeof(char *);
	cout << "sizeof(char *)" << size << endl;	

	cout << len << endl;
	cout << tmp << endl;
	cout << (tmp >> 3) << endl;

	cout << "=========================" << endl;
	int start = 10;
	int end = 17;
	int start_pos = start / 8;
	int count = ((end % 8 ) == 0)?0: 1;
	int end_pos = (end / 8) + (((end % 8 ) == 0)?0: 1);
	
	
	cout << "start_pos " << start_pos << endl;
	cout << "end_pos " << end_pos << endl;
	cout << "count " << count << endl;

	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	char buffer[512] = {0};
	sprintf(buffer, "%s", "abcdef");
	cout << strlen(buffer) << ":" <<  buffer << endl; 
	sprintf(buffer, "%s", "zw");
	cout << strlen(buffer) << ":" <<  buffer << endl; 

	return 0;
}
