#include <gtest/gtest.h>
#include "QueueMemoryResource.h"

TEST(AllocateAndDeallocate, Test) {
    QueueMemoryResource memoryResource(1024);

    void* ptr1 = memoryResource.allocate(32, alignof(int));
    void* ptr2 = memoryResource.allocate(64, alignof(double));

    ASSERT_NE(ptr1, nullptr);
    ASSERT_NE(ptr2, nullptr);

    memoryResource.deallocate(ptr1, 32, alignof(int));
    memoryResource.deallocate(ptr2, 64, alignof(double));
}

TEST(MemoryReusability, Test) {
    QueueMemoryResource memoryResource(1024);

    void* ptr1 = memoryResource.allocate(32, alignof(int));
    memoryResource.deallocate(ptr1, 32, alignof(int));
    void* ptr2 = memoryResource.allocate(32, alignof(int));

    ASSERT_EQ(ptr1, ptr2);
}

TEST(Destructor, Test) {
    QueueMemoryResource* memoryResource = new QueueMemoryResource(1024);
    delete memoryResource;
}

TEST(IsEqual, Test) {
    QueueMemoryResource memoryResource1(1024);
    QueueMemoryResource memoryResource2(1024);

    ASSERT_TRUE(memoryResource1.is_equal(memoryResource1));
    ASSERT_FALSE(memoryResource1.is_equal(memoryResource2));
}
