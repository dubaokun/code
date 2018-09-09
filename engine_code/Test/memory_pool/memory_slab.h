#ifndef __MEMORY_SLAB_H__
#define __MEMORY_SLAB_H__

#include <stdint.h>
#include <vector>
#include <string>

namespace profile {
namespace cache {

#define CHUNK_ALIGN_BYTES 8

class MemorySlab {
public:
	MemorySlab();
	~MemorySlab();

public:
	void statics();
	void showInfo(void * pstr);
	bool init(uint32_t item_size, uint32_t item_count, std::string table_name);

	void * get();
	void release(void * pstr);
		
private:
	void do_slabs_free(void * pstr);

private:
	void * slab_;											// the address of malloc memory
	uint32_t slab_limit_;									// the limit size of malloc memory

	uint32_t item_size_;									// the size of item
	uint32_t item_count_;									// the count of total items
	std::string table_name_;

	uint32_t sl_curr_;										// free item count
	std::vector<void *> slots_;									// free item to use

	//void * slots_; 											// 回收来的内存块（映射成item链表）
	//uint32_t sl_curr_;										// slots中包含多少个chunk			
	
};

}
}
#endif
