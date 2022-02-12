#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 10000000

using namespace std;

struct CacheItem {
    CacheItem()
    {
        cout << "get it" << endl;
        reset();
    }
    virtual ~CacheItem() 
    {
        cout << "del it" << endl;
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

void test()
{
    int count = 100;
    int size = sizeof(CacheItem *);
    CacheItem* item = (CacheItem*)malloc(size * count);
    if (NULL == item) {
        cout << "malloc fail return" << endl;
        return;
    }

    memset(item, 0x00, size * count);
    
    for (int i = 0; i < count; ++i) {
        CacheItem * pP = item + i;
        pP->key = i;
    }

    for (int i = 0; i < count; ++i) {
        cout << (item + i)->key << endl;
    } 
}



int main(int argc, char ** argv)
{
    
	void * p1 = NULL;
	char * p2 = NULL;
	int * p3 = NULL;
	cout << "void *=" << sizeof(p1) << " char *=" << sizeof(p2) << " int*=" << sizeof(p3) << endl;

    cout << sizeof(CacheItem*) << endl;
    cout << "==========================" << endl;
    CacheItem ** item = new CacheItem*[10000000];
    sleep(2);
    cout << "==========================" << endl;
    delete []item;
    
    while(1)
        sleep(1);
	return 0;
}
