#ifndef __PROFILE_SEGMENT_LRU_CACHE_H__
#define __PROFILE_SEGMENT_LRU_CACHE_H__

#include <string>
#include <vector>
#include <pthread.h>

#define SEGMENT_COUNT 1024
#define SEGMENT_SIZE (64 * SEGMENT_COUNT)

// 文件片段控制块结构体
#pragma pack(1)
struct SegmentControl {
	uint32_t index_;								// 文件片段控制块的index
	uint32_t capicity_;								// 文件片段控制块的可以容纳的segment的数量 （防止内存暴涨，计算方式：_count * rotio配置）
	pthread_spintlock_t lock_;						// 文件片段控制块的自旋锁；
};
#pragma pack()

// 单个文件片段的LRU，使用hash和双向链表实现

class ProfileSegmentLruCache 
{
public:
	ProfileSegmentLruCache(size_t segment_size);   
	~ProfileSegmentLruCache();

	int get(docid_t docid, doc_t*& doc);						// 获取某个docid的正排信息：docid->file+offset->index+file+offset

private:
	// 计算某个文件的某个偏移在哪几个片段中
	int calc_file_name_count(const std::string& str);														// 根据文件名计算数值
	int calc_offset_segment(const std::string& file_name, const size_t& offset_pos, const int& length, std::vector<int>& result); // 计算某个文件某个偏移的segment片段 
	int read_main_from_cache(const std::string& file_name, const size_t& offset_pos,  	

	// 从某个片段读取数据
	int get_result(const std::string& file_name, const size_t& offset_pos, const int& length);	// 存储几个分片，分别从某个分片读取缓存，读取磁盘，写入磁盘；	
	
private:
	size_t segment_size_;
	std::vector<SegmentControl> segments_;		// 文件片段控制块结构体的集合（总共多少，从配置中传个配置文件）减少锁冲突，lru整体化，	
	std::vector<LruList> 		lrus_;			// 文件片段的lru算法的集合（与片段控制块的大小一致）
};

#endif
