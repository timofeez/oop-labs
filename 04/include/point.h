#pragma once

template <class T>
class point {
public:
    T x, y;

    point(T x = 0, T y = 0) : x(x), y(y) {}

    point(const point<T>& other) : x(other.x), y(other.y) {}

    point<T>& operator=(const point<T>& other) {
        if (this == &other) return *this;
        x = other.x;
        y = other.y;
        return *this;
    }

    point(point<T>&& other) noexcept : x(other.x), y(other.y) {}

    point<T>& operator=(point<T>&& other) noexcept {
        if (this == &other) return *this;
        x = other.x;
        y = other.y;
        return *this;
    }
};
