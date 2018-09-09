#include <stdio.h>
#include <malloc.h>

int main()
{
	mallopt(M_TRIM_THRESHOLD, -1);
	char a = ' ';
	char b = ' ';
	if(a == b)
		printf("kongge == kongge\n");		
}
