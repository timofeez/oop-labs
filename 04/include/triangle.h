#pragma once
#include "figure.h"
#include <iostream>
#include <stdexcept>

template <class T>
class triangle : public figure<T> {
private:
    T base, height;
    std::unique_ptr<point<T>> center;

public:
    triangle(T base = 0, T height = 0)
        : base(base), height(height), center(std::make_unique<point<T>>(base / 2, height / 3)) {}

    double area() const override {
        return 0.5 * base * height;
    }

    std::unique_ptr<point<T>> get_center() const override {
        return std::make_unique<point<T>>(*center);
    }

    void print() const override {
        std::cout << "Triangle: Coordinates: (" << center->x << ", " << center->y 
                  << "), Base: " << base << ", Height: " << height << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const triangle<T>& triangle) {
        os << "Triangle: Base: " << triangle.base << ", Height: " << triangle.height;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, triangle<T>& triangle) {
        std::cout << "Enter base and height for the triangle: ";
        is >> triangle.base >> triangle.height;
        if (is.fail()) throw std::invalid_argument("Invalid input for Triangle!");
        triangle.center = std::make_unique<point<T>>(triangle.base / 2, triangle.height / 3);  // Update center
        return is;
    }
};
