#include <iostream>
#include <stdint.h>

using namespace std;

struct CacheItem {
    CacheItem()
    {
        reset();
    }
    virtual ~CacheItem() 
    {
        reset();
    }
    void reset()
    {
        key = 0;
        hash_next = NULL;
    }
    uint64_t   key;        //该item保存的查询key
    CacheItem  *hash_next; //在map中对应的next指针
};

int main(int argc, char ** argv)
{
	void * p1 = NULL;
	char * p2 = NULL;
	int * p3 = NULL;
	cout << "void *=" << sizeof(p1) << " char *=" << sizeof(p2) << " int*=" << sizeof(p3) << endl;

    cout << sizeof(CacheItem*) << endl;
	return 0;
}
