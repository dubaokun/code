#include "memory_slab.h"
#include <iostream>

#define ITEM_SIZE 50
#define ITEM_COUNT 2 
#define TABLE_NAME "tmp"

profile::cache::MemorySlab* slab = NULL ;

void test(char a, char b, int end)
{
	char * p1 = (char *)slab->get();
	char * p2 = (char *)slab->get();

	if (NULL == p1) {
		std::cout << "get p1 NULL" << std::endl;
		return;
	}

	if (NULL == p2) {
		std::cout << "get p2 NULL" << std::endl;
		return;
	}

	for (int i = 0; i < ITEM_SIZE - end; ++i) {
		p1[i] = a;
	}

	for (int i = 0; i < ITEM_SIZE - end; ++i) {
		p2[i] = b;
	} 

	//slab->statics();
	slab->release(p1);
	slab->release(p2);
	slab->statics();

}

int main(int argc, char ** argv)
{
	slab = new profile::cache::MemorySlab(); 
	slab->init(ITEM_SIZE, ITEM_COUNT, TABLE_NAME);


	while(1)
	{	
		test('a', 'b', 0);
		test('c', 'd', 2);
		sleep(10);
	}

	while(1)
		sleep(1);

	return 0;
}
