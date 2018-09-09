#ifndef __SEGMENT_DOC_INFO__H__
#define __SEGMENT_DOC_INFO__H__

#include <time.h>
#include <stdint.h>

typedef char doc_t; 
typedef uint32_t handle_t;

namespace profile {
namespace cache {
namespace detail {    

#pragma pack(8)
class SegmentDocInfo
{
    doc_t* doc_;					// doc data address; NULL not in cache
    handle_t handle_;				// handle to lru; default 0
	time_t time_;					// delete latter for several seconds
    
public:
    SegmentDocInfo();

	// get doc data address 
    void getDoc(doc_t*& doc);
	
	// get doc handle in doublelist
    void getHandle(handle_t& handle);

	// get accsess time
	void getTime(time_t& t);

	// set doc data address
	bool setDoc(doc_t* doc);

	// set doc handle in double
    bool setHandle(handle_t handle);

	// set accsess time
	bool setTime(time_t t);

	// release doc in hashtable, but free latter 
	bool releaseAll();

};
#pragma pack()


}
}
}


#endif
