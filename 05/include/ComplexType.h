#ifndef COMPLEX_TYPE_H
#define COMPLEX_TYPE_H

#include <string>

struct ComplexType {
    int id;
    std::string name;

    ComplexType(int id, const char* name) : id(id), name(name) {}
};

#endif
