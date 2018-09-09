#ifndef __PROFILE_LRU_CACHE__H__
#define __PROFILE_LRU_CACHE__H__

#include <vector>
#include <map>
#include <string>
#include <pthread.h>
#include "segment_doc_info.h"
#include "double_linked_array_list.h"

typedef int32_t docid_t;

namespace profile {
namespace cache {

using namespace detail;


class ProfileSegmentLruCache
{
    typedef DoubleLinkedArrayList<docid_t> LruList;

public:
    /**
     * @brief ctor
     *
     * @param thread_count
     * @param cache_count_per_thread
     * @param doc_count
     */
    ProfileSegmentLruCache(uint32_t doc_count, uint32_t segment_count, uint32_t cache_count_per_segment, int unit_len);

    /**
     * @brief dtoc
     */
    ~ProfileSegmentLruCache();

    /**
     * @brief Get doc
     *
     * @param docid
     * @param doc
     *
     * @return Error Code
     */
    int get(docid_t docid, doc_t*& doc);

    /**
     * @brief Put doc when doc_ is NULL
     *
     * @param docid
     * @param doc
     * @param replaceable
     *
     * @return Error Code
     *         E_OK         current thread own this doc and the doc is put succeed
     *         E_INVDID     docid is invalid
     *         E_INVAG      doc is NULL
     *         E_INVWTID    wtid is invalid
     *         E_UNSP       current thread is update thread and the doc is replaceable
     *         E_NPMT       this doc is owned by other thread
     *         E_FSDF       current thread has own this doc and a valid doc is put already
     */
    int put(docid_t docid, doc_t* doc, bool replaceable = true);

    /**
     * @brief Simple version get
     *
     * @param docid
     * @param doc
     *
     * @return True if a valid doc is get
     */
    bool simpleGet(docid_t docid, doc_t*& doc);

    /**
     * @brief Simple version put
     *
     * @param docid
     * @param doc
     * @param replaceable
     *
     * @return True if the doc is put by a thread and a valid doc is get
     *
     * @warning Param doc may be changed because other thread set the doc first.
     *          This function may try some time because failed to set the flag.
     */
    bool simplePut(docid_t docid, doc_t*& doc, bool replaceable = true);

    /**
     * @brief Update doc when doc_ is not NULL
     *
     * @param docid
     * @param doc
     *
     * @return Error Code
     */
    int update(docid_t docid, doc_t* doc, bool delete_instant = false);

    /**
     * @brief Delete a doc by docid. 
     *
     * @param docid
     *
     * @return Error Code
     *
     * @warning Only support unreplaceable doc now.
     */
    int del(docid_t docid);

    /**
     * @brief Get some statistic data
     *
     * @param result
     *
     * @warning Accurate result can not be got.
     */
    void statistic(std::map<std::string, int32_t>& result);

    /**
     * @brief Get cached docid whose doc_ is not NULL
     *
     * @param docids
     */
    void cachedDocid(std::vector<docid_t>& docids);

    /**
     * @brief Warm put. This is used to warm cache.
     *
     * @param docid
     * @param doc
     * @param replaceable
     *
     * @return True if put succeed. 
     *
     * @warning This function can not called with other thread synchronously.
     */
    bool warmPut(docid_t docid, doc_t* doc, bool replaceable = true);

private:
	int getSegNumber(docid_t docid, int& seg_number);

    void evict(int seg_number);

    ProfileSegmentLruCache(const ProfileSegmentLruCache&);
    ProfileSegmentLruCache& operator=(const ProfileSegmentLruCache&);

private:
    const uint32_t doc_count_;																// 总共的docid
    const uint32_t segment_count_;															// 总共的分区数量				
    const uint32_t cache_count_per_segment_;												// 每个分配的docid数量
	const int unit_len_;																	// 正排固定长度大小

    std::vector<LruList> segment_lrus_;
	//SegmentDocInfo* segment_tables_[1024];
	std::vector<SegmentDocInfo*> segment_tables_;
	pthread_spinlock_t* segment_locks_;

};


}
}
#endif
