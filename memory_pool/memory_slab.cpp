#include "memory_slab.h"
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <iostream>

namespace profile {
namespace cache {

MemorySlab::MemorySlab() : 
	slab_(NULL),
	slab_limit_(0),
	item_size_(0),
	item_count_(0),
	table_name_(""),
	sl_curr_(0)
{

}
	

MemorySlab::~MemorySlab()
{
	if (NULL != slab_) {
		delete [](char *)slab_;
		slab_ = NULL;
	}

	slots_.clear();
}

bool MemorySlab::init(uint32_t item_size, uint32_t item_count, std::string table_name)
{
	if (0 >= item_size || 0 >= item_count || 0 == table_name.size()) return false;

	item_size_ = item_size;
	item_count_ = item_count;
	table_name_ = table_name;
	
	// aligned the item_size by 8 byte
	if (item_size_ % CHUNK_ALIGN_BYTES) {
		item_size_ += CHUNK_ALIGN_BYTES - (item_size_ % CHUNK_ALIGN_BYTES);
	}

	// allocate memory	
	slab_limit_ = item_size_ * item_count_;
	slab_ = new(std::nothrow)char[slab_limit_]; 		
	if (NULL == slab_) {
		char buffer[256] = {0};
		sprintf(buffer, "table=[%s]new memory pool failed!", table_name_.c_str());
		throw std::runtime_error(buffer);
		return false;
	}

	fprintf(stderr, "table=[%s] new memory=[%d] item_size=[%d] item_count[%d]\n", table_name_.c_str(), slab_limit_, item_size_, item_count_);
	
	// add into vector for free item	
	char * pstr = (char *)slab_;
	for (int i = 0; i < item_count_; ++i) {
		do_slabs_free(pstr);
		pstr += item_size_;		
	}	

	return true;
}

void MemorySlab::do_slabs_free(void * pstr)
{
	//memset(pstr, 0x00, item_size_);
	slots_.push_back(pstr);	
	sl_curr_ ++;
}

void * MemorySlab::get()
{
	if (sl_curr_ <= 0 ) return NULL;
	
	void * tt = slots_.back();
	slots_.pop_back(); 
	sl_curr_ --;

	return tt;
}

void MemorySlab::release(void * pstr) 
{
	do_slabs_free(pstr);
}

void MemorySlab::statics()
{
	std::cout << "===========================statics===============================" << std::endl;	
	std::cout << "item_size=" << item_size_ << std::endl;
	std::cout << "item_count=" << item_count_ << std::endl;
	std::cout << "slab_limit=" << slab_limit_ << std::endl;
	std::cout << "slots count=" << sl_curr_ << std::endl;
	for (int i = 0; i < item_count_; ++i) {
		std::cout << (char *)slab_ + (i * item_size_) << std::endl;
	} 
	std::cout << "===========================statics===============================" << std::endl;	
}

void MemorySlab::showInfo(void * pstr) 
{
}
	
}
}
