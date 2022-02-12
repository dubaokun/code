#include <cassert>
#include "segment_doc_info.h"


namespace profile {
namespace cache {
namespace detail{    

static const handle_t kInvalidHandle = 0;

SegmentDocInfo::SegmentDocInfo() : doc_(NULL), handle_(kInvalidHandle), time_(time(NULL)) {
}

void SegmentDocInfo::getDoc(doc_t*& doc) {
    doc = doc_;
}

void SegmentDocInfo::getHandle(handle_t& handle) {
    handle = handle_;
}

void SegmentDocInfo::getTime(time_t& t) {
	t = time_;
}

bool SegmentDocInfo::setDoc(doc_t* doc){
	doc_ = doc;
	return true;
}

bool SegmentDocInfo::setHandle(handle_t handle){
	handle_ = handle;
	return true;
}

bool SegmentDocInfo::setTime(time_t t) {
	time_ = t;
}

bool SegmentDocInfo::releaseAll() {
	doc_ = NULL;
	handle_ = kInvalidHandle;
	time_ = time(NULL);
	return true;
}


}
}
}

