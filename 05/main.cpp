#include "Queue.h"
#include "QueueMemoryResource.h"
#include <iostream>
#include <string>
#include "ComplexType.h"

int main() {
    QueueMemoryResource memoryResource(1024);

    Queue<int> intQueue(&memoryResource);
    intQueue.push(10);
    intQueue.push(20);

    std::cout << "Queue size: " << intQueue.get_size() << std::endl;
    std::cout << "Popped: " << intQueue.pop() << std::endl;
    std::cout << "Popped: " << intQueue.pop() << std::endl;

    Queue<ComplexType> complexQueue(&memoryResource);
    complexQueue.push(ComplexType(1, "Object A"));
    complexQueue.push(ComplexType(2, "Object B"));

    std::cout << "Queue size: " << complexQueue.get_size() << std::endl;
    ComplexType obj1 = complexQueue.pop();
    std::cout << "Popped: " << obj1.name << std::endl;
    ComplexType obj2 = complexQueue.pop();
    std::cout << "Popped: " << obj2.name << std::endl;

    return 0;
}
