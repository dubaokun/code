#include <iostream>
#include<stdexcept>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

using namespace std;

// -------------------------------------------------------------------
const uint32_t kReplaceableBit = 1;
const uint32_t kReplaceableMask = (1 << kReplaceableBit) - 1;
const uint32_t kReplaceableShift = 0;
const uint32_t kReplaceable = 0x1;
const uint32_t kUnreplaceable = 0x0;

const uint32_t kOwnerBit = 10;
const uint32_t kOwnerMask = (1 << kOwnerBit) - 1;
const uint32_t kOwnerMax = kOwnerMask;
const uint32_t kOwnerShift = kReplaceableShift + kReplaceableBit ;

// --------------------------------------------------------------------
const static char DELIM = '\01';           //常用的分隔符
const static char DELIM2 = '\02';          //常用的分隔符
const static char DELIM3 = '\03';          //常用的分隔符

// ------------------ print 二进制 -------------------------------------
void f(int n)   
{   
    if(n)   
        f(n/2);   
    else   
        return;   
    printf("%d",n%2);   
} 

void printf_macro()
{
	f(kReplaceableBit); printf("\n");
	f(kReplaceableMask);printf("\n");
	f(kOwnerBit);printf("\n");
	f(kOwnerMask); printf("\n");
	f(kOwnerMax);printf("\n");
	f(kOwnerShift);printf("\n");

}

void t1()
{
	FILE * fp = fopen("./tmp.txt", "w+");
	char buffer[1024] = {0};
	sprintf(buffer, "a%cb%cc%c", DELIM, DELIM2, DELIM3);
	fwrite(buffer, strlen(buffer), 1, fp);
	fclose(fp);
}

int main()
{
	while(1) {
		char * pstr = NULL;
		delete [] pstr;
	}
	//////////////////////////////////////
	t1();
	size_t start = (size_t)pow(2, 64) - 1;
	cout << sizeof(size_t) << endl;
	cout << sizeof(long) << endl;
	cout << start << endl;

	uint32_t tmp = 1 << kOwnerBit;
	cout << "---: " << tmp << endl;

	//throw std::runtime_error("aaa");

	cout << "|||" << (1 << kOwnerBit) << endl;
	cout << "=================================" << endl;
	cout << INT_MAX << endl; 

	cout << "=================================" << endl;
	cout << kReplaceable << endl;
	
	cout << "=================================" << endl;
	cout << kOwnerMask << endl;
	cout << "=================================" << endl;
	cout << kReplaceableBit << endl;
	cout << kReplaceableMask << endl;

	while(1)
		sleep(1);

	return 0;
}
