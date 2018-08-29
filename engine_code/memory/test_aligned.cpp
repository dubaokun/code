#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char ** argv)
{
	char * _unreplace_mem_arena = new char[90007 + 7];
	fprintf(stderr, "+++++++++++++++++++++++%p before\n", _unreplace_mem_arena);
	_unreplace_mem_arena = (char*)(((long)_unreplace_mem_arena+7)&(~7L));
	fprintf(stderr, "+++++++++++++++++++++++%p after\n", _unreplace_mem_arena);	
	
}
