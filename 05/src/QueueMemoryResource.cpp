#include "QueueMemoryResource.h"
#include <algorithm>

QueueMemoryResource::QueueMemoryResource(size_t max_size) : max_size_(max_size), allocated_size_(0) {}

QueueMemoryResource::~QueueMemoryResource() {
    for (auto block : blocks_) {
        ::operator delete(block);
    }
}

void* QueueMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    if (allocated_size_ + bytes > max_size_) {
        throw std::bad_alloc();
    }
    allocated_size_ += bytes;
    void* ptr = ::operator new(bytes, std::align_val_t(alignment));
    blocks_.push_back(ptr);
    return ptr;
}

void QueueMemoryResource::do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) {
    allocated_size_ -= bytes;
    auto it = std::find_if(blocks_.begin(), blocks_.end(),
        [ptr](const void* block_ptr) { return block_ptr == ptr; });

    if (it != blocks_.end()) {
        blocks_.erase(it);
    }

    ::operator delete(ptr, std::align_val_t(alignment));
}

bool QueueMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
