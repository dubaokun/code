/*
 *  思考问题：
 *      实际的物理存储位置；
 *      单链表的逻辑组织形式；
 *      双链表的逻辑组织形式；
 *
 *  应用场景：
 *      配合LRUcache使用的lru list，用于将存储
 *
 *  空闲队列：
 *      仅仅用于记录未使用的node元素，单链表足以；
 *
 *  使用队列：双向队列
 *      单链表只有下一个节点的信息，对于使用队列进行存储数据需要进行调整的情况
 *  来说，需要进行调整：移动、删除，这样需要修改前后节点的信息。所以需要的是双
 *  链表的形式。
 *
 */

#pragma once

#include <cassert>
#include <stdexcept>
#include <boost/smart_ptr.hpp>


template <typename value_type>
class DoubleLinkedArrayList
{
public:
    typedef size_t handle_t;
    typedef value_type& reference;
    static const handle_t invalid_handle = 0;

private:
    struct Node
    {
        Node() : prev(invalid_handle), next(invalid_handle) {}
        handle_t prev;
        handle_t next;
        value_type value;
    };
    typedef Node node_type;

    static const handle_t sentry_node_handle = invalid_handle;

public:
    DoubleLinkedArrayList(size_t n = 1) {
        if (0 == n) {
            n = 1;
        }
        capacity_ = n;
        // One more item, the 0th item is invalid
        data_.reset(new node_type[capacity_ + 1]);
        clear();
    }

    ~DoubleLinkedArrayList() {
        release();
    }

    const handle_t pushFront(const value_type& v) {
        assert(capacity_ > size_);
        if (capacity_ == size_) {
            return invalid_handle;
        }
        node_type& sentry_node = data_[sentry_node_handle];

        handle_t hd = allocate();
        node_type& node = data_[hd];
        node.prev = sentry_node_handle;
        node.next = sentry_node.next;
        node.value = v;

        data_[sentry_node.next].prev = hd;
        sentry_node.next = hd;
        return hd;
    }

    const handle_t pushBack(const value_type& v) {
        assert(capacity_ > size_);
        if (capacity_ == size_) {
            return invalid_handle;
        }
        node_type& sentry_node = data_[sentry_node_handle];

        handle_t hd = allocate();
        node_type& node = data_[hd];
        node.prev = sentry_node.prev;
        node.next = sentry_node_handle;
        node.value = v;

        data_[sentry_node.prev].next = hd;
        sentry_node.prev = hd;
        return hd;
    }

    bool popFront() {
        assert(0 != size_);
        if (0 == size_) {
            return false;
        }
        node_type& sentry_node = data_[sentry_node_handle];
        handle_t hd = sentry_node.next;
        sentry_node.next = data_[hd].next;
        data_[sentry_node.next].prev = sentry_node_handle;

        deallocate(hd);
        return true;
    }

    bool popBack() {
        assert(0 != size_);
        if (0 == size_) {
            return false;
        }
        node_type& sentry_node = data_[sentry_node_handle];
        handle_t hd = sentry_node.prev;
        sentry_node.prev = data_[hd].prev;
        data_[sentry_node.prev].next = sentry_node_handle;

        deallocate(hd);
        return true;
    }


    bool moveToHead(handle_t hd) {
        if (!checkHandle(hd)) {
            return false;
        }

        if (!isInDataList(hd)) {
            assert(NULL && hd && "handle should not in free list!");
            return false;
        }

        assert(0 != size_);
        if (0 == size_) {
            return false;
        }

        // erase
        node_type& node = data_[hd];
        data_[node.prev].next = node.next;
        data_[node.next].prev = node.prev;

        // push front
        node_type& sentry_node = data_[sentry_node_handle];
        node.prev = sentry_node_handle;
        node.next = sentry_node.next;

        data_[sentry_node.next].prev = hd;
        sentry_node.next = hd;

        return true;
    }

    bool erase(handle_t hd) {
        if (!checkHandle(hd)) {
            return false;
        }

        if (!isInDataList(hd)) {
            assert(NULL && hd && "handle should not in free list!");
            return false;
        }

        assert(0 != size_);
        if (0 == size_) {
            return false;
        }

        node_type& node = data_[hd];
        data_[node.prev].next = node.next;
        data_[node.next].prev = node.prev;

        deallocate(hd);
        return true;
    }

    reference at(handle_t hd) {
        if (!checkHandle(hd) || !isInDataList(hd)) {
            assert(NULL && "error handle");
            throw std::range_error("invalid handle");
        }
        return data_[hd].value;
    }

    reference front() {
        assert(0 != size_);
        if (0 == size_) {
            throw std::logic_error("empty list");
        }
        node_type& sentry_node = data_[sentry_node_handle];
        return data_[sentry_node.next].value;
    }

    reference back() {
        assert(0 != size_);
        if (0 == size_) {
            throw std::logic_error("empty list");
        }
        node_type& sentry_node = data_[sentry_node_handle];
        return data_[sentry_node.prev].value;
    }

    size_t size() const { return size_;}

    size_t capacity() const { return capacity_;}

    bool full() const { return size_ == capacity_;}

    void clear() {
        assert(1 <= capacity_);
        size_ = 0;

        data_[sentry_node_handle].prev = data_[sentry_node_handle].next = sentry_node_handle;

        handle_t next = invalid_handle;
        for (handle_t i = capacity_; i > 0; --i) {
            data_[i].prev = invalid_handle;
            data_[i].next = next;
            next = i;
        }
        free_head_ = 1;
    }

    bool resize(size_t n) {
        if (n <= capacity_) 
            return false;

        boost::shared_array<node_type> new_data(new (std::nothrow) node_type[n + 1]);
        if (NULL == new_data) 
            return false;

        for (handle_t i = 0; i <= capacity_; ++i) {
            new_data[i] = data_[i];
        }
        data_ = new_data;

        handle_t next = free_head_;
        for (handle_t i = n; i > capacity_; --i) {
            data_[i].prev = invalid_handle;
            data_[i].next = next;
            next = i;
        }
        free_head_ = capacity_ + 1;
        capacity_ = n;

        return true;
    }

private:
    void release() {
        capacity_ = 0;
        size_ = 0;
        free_head_ = invalid_handle;
        data_.reset();
    }

    handle_t allocate() {
        assert(capacity_ != size_);

        ++size_;

        handle_t hd = free_head_;
        free_head_ = data_[free_head_].next;

        return hd;
    }

    void deallocate(handle_t hd) {
        assert(checkHandle(hd));
        assert(0 != size_);

        node_type& node = data_[hd];
        node.prev = invalid_handle;
        node.next = free_head_;
        free_head_ = hd;

        --size_;
    }

    bool checkHandle(handle_t hd) {
        return hd > 0 && hd <= capacity_;
    }

    bool isInDataList(handle_t hd) {
        assert(checkHandle(hd));
        if (invalid_handle == hd) {
            return false;
        }

        node_type& sentry_node = data_[sentry_node_handle];
        node_type& node = data_[hd];
        if ((invalid_handle == node.prev && hd != sentry_node.next) 
                || (invalid_handle == node.next && hd != sentry_node.prev)) {
            return false;
        }
        return true;
    }
private:
    size_t size_;
    size_t capacity_;

    // free list is single linked list
    // becaused it is used to check erase params
    handle_t free_head_ ;

    boost::shared_array<node_type> data_;
};

