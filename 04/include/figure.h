#pragma once
#include <memory>
#include <cmath>
#include "point.h"

template <class T>
class figure {
public:
    virtual ~figure() = default;

    virtual double area() const = 0;

    virtual std::unique_ptr<point<T>> get_center() const = 0;

    virtual void print() const = 0;

    virtual operator double() const {
        return area();
    }
};
