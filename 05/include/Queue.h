#pragma once
#include "QueueMemoryResource.h"
#include <memory>
#include <stdexcept>
#include <iterator>

template <typename T>
class Queue {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& value) : value(value), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    size_t size_;
    std::pmr::polymorphic_allocator<Node> allocator_;

public:
    explicit Queue(QueueMemoryResource* customAllocator)
        : head_(nullptr), tail_(nullptr), size_(0), allocator_(customAllocator) {}

    ~Queue() {
        clear();
    }

    size_t get_size() const {
        return size_;
    }

    void push(const T& value) {
        Node* newNode = std::allocator_traits<std::pmr::polymorphic_allocator<Node>>::allocate(allocator_, 1);
        std::allocator_traits<std::pmr::polymorphic_allocator<Node>>::construct(allocator_, newNode, value);
        
        if (tail_) {
            tail_->next = newNode;
        }
        tail_ = newNode;
        if (!head_) {
            head_ = newNode;
        }
        ++size_;
    }

    T pop() {
        if (!head_) throw std::runtime_error("Queue is empty");

        Node* tmp = head_;
        T value = head_->value;
        head_ = head_->next;
        
        std::allocator_traits<std::pmr::polymorphic_allocator<Node>>::destroy(allocator_, tmp);
        std::allocator_traits<std::pmr::polymorphic_allocator<Node>>::deallocate(allocator_, tmp, 1);

        --size_;
        return value;
    }

    void clear() {
        while (head_) {
            Node* tmp = head_;
            head_ = head_->next;
            std::allocator_traits<std::pmr::polymorphic_allocator<Node>>::destroy(allocator_, tmp);
            std::allocator_traits<std::pmr::polymorphic_allocator<Node>>::deallocate(allocator_, tmp, 1);
        }
        tail_ = nullptr;
        size_ = 0;
    }

    class iterator : public std::iterator<std::forward_iterator_tag, T> {
    private:
        Node* node_;

    public:
        iterator(Node* node) : node_(node) {}

        T& operator*() { return node_->value; }

        iterator& operator++() {
            node_ = node_->next;
            return *this;
        }

        bool operator==(const iterator& other) const { return node_ == other.node_; }

        bool operator!=(const iterator& other) const { return node_ != other.node_; }
    };

    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(nullptr); }
};
