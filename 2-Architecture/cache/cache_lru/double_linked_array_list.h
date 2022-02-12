/*
 *  好处：
 *      循环使用内存，减少内存碎片，减少内存分片释放的时间，池化
 *  坏处：
 *      容量大小受限
 *
 *  内存消耗：
 *      1）链表的消耗：每个node有两个指针，是否可以精简为一个指针呢
 *
 *  逻辑：
 *      1）空闲节点用链表单向链接起来
 *      2）使用节点用链表双向链接起来，头节点是固定的哨兵位置
 */

#pragma once

#include <cassert>
#include <stdexcept>
#include <vector>


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
        data_.resize(capacity_ + 1);
        clear();
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
	bool approached_full() const { return size_ >= (capacity_ * 0.95); }

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

        data_.resize(n + 1);

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

    std::vector<node_type> data_;
};

