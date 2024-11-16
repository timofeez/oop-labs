#pragma once
#include "figure.h"
#include <iostream>

template <class T>
class square : public figure<T> {
private:
    T side;
    std::unique_ptr<point<T>> center;

public:
    square(T side = 0) : side(side), center(std::make_unique<point<T>>(side / 2, side / 2)) {}

    double area() const override {
        return side * side;
    }

    std::unique_ptr<point<T>> get_center() const override {
        return std::make_unique<point<T>>(*center);
    }

    void print() const override {
        std::cout << "Square: Coordinates: (" << center->x << ", " << center->y
                  << "), Side: " << side << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const square<T>& square) {
        os << "Square: Side: " << square.side;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, square<T>& square) {
        std::cout << "Enter side length for the square: ";
        is >> square.side;
        if (is.fail()) throw std::invalid_argument("Invalid input for Square!");
        square.center = std::make_unique<point<T>>(square.side / 2, square.side / 2);  // Update center
        return is;
    }
};
