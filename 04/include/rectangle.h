#pragma once
#include "figure.h"
#include <iostream>
#include <stdexcept>

template <class T>
class rectangle : public figure<T> {
private:
    T width, height;
    std::unique_ptr<point<T>> center;

public:
    rectangle(T width = 0, T height = 0)
        : width(width), height(height), center(std::make_unique<point<T>>(width / 2, height / 2)) {}

    double area() const override {
        return width * height;
    }

    std::unique_ptr<point<T>> get_center() const override {
        return std::make_unique<point<T>>(*center);
    }

    void print() const override {
        std::cout << "Rectangle: Coordinates: (" << center->x << ", " << center->y 
                  << "), Width: " << width << ", Height: " << height << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const rectangle<T>& rectangle) {
        os << "Rectangle: (" << rectangle.width << " x " << rectangle.height << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, rectangle<T>& rectangle) {
        std::cout << "Enter width and height for the rectangle: ";
        is >> rectangle.width >> rectangle.height;
        if (is.fail()) throw std::invalid_argument("Invalid input for Rectangle!");
        rectangle.center = std::make_unique<point<T>>(rectangle.width / 2, rectangle.height / 2);  // Update center
        return is;
    }
};
