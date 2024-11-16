#pragma once
#include <memory_resource>
#include <vector>
#include <cstddef>
#include <new>
#include <iostream>

class QueueMemoryResource : public std::pmr::memory_resource {
public:
    explicit QueueMemoryResource(size_t max_size);

    ~QueueMemoryResource();

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* ptr, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    size_t max_size_;
    size_t allocated_size_;
    std::vector<void*> blocks_;
};
