#include "Queue.h"
#include "QueueMemoryResource.h"
#include <gtest/gtest.h>
#include "ComplexType.h"

TEST(DefaultConstructor_Test, TestBody) {
    QueueMemoryResource memoryResource(1024);
    Queue<int> queue(&memoryResource);
    int result = queue.get_size();
    ASSERT_EQ(result, 0);
}

TEST(PushAndPop_Test, TestBody) {
    QueueMemoryResource memoryResource(1024);
    Queue<int> queue(&memoryResource);
    queue.push(10);
    queue.push(20);
    int size = queue.get_size();
    int firstPop = queue.pop();
    int secondPop = queue.pop();
    ASSERT_EQ(size, 2);
    ASSERT_EQ(firstPop, 10);
    ASSERT_EQ(secondPop, 20);
}

TEST(ComplexTypeQueue_Test, TestBody) {
    QueueMemoryResource memoryResource(1024);
    Queue<ComplexType> queue(&memoryResource);
    queue.push(ComplexType(1, "Object A"));
    queue.push(ComplexType(2, "Object B"));
    int size = queue.get_size();
    ComplexType firstPop = queue.pop();
    ComplexType secondPop = queue.pop();
    ASSERT_EQ(size, 2);
    ASSERT_EQ(firstPop.name, "Object A");
    ASSERT_EQ(secondPop.name, "Object B");
}

TEST(ClearAndSize_Test, TestBody) {
    QueueMemoryResource memoryResource(1024);
    Queue<int> queue(&memoryResource);
    queue.push(10);
    queue.push(20);
    queue.push(30);
    queue.clear();
    int result = queue.get_size();
    ASSERT_EQ(result, 0);
}
