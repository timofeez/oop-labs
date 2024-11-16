#ifndef THREE_H
#define THREE_H

#include <string>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

// Класс Array
class Array {
public:
    Array();
    explicit Array(size_t size);
    Array(const std::initializer_list<unsigned char>& digits);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array() noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    size_t size() const;
    unsigned char& operator[](size_t index);
    const unsigned char& operator[](size_t index) const;

    Array& operator+=(const Array& other);
    Array& operator-=(const Array& other);

    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;
    bool operator<(const Array& other) const;
    bool operator>(const Array& other) const;

    static void normalizeSize(Array& a, Array& b);

    void resize(size_t newSize);

protected:
    unsigned char* _digits;
    size_t _capacity;
    size_t _size;
    void trimLeadingZeros();
};

class Three : public Array {
public:
    Three();
    explicit Three(const std::string& threeStr);
    Three(const Three& other);
    Three(Three&& other) noexcept;
    ~Three() noexcept;

    Three& operator=(const Three& other);
    Three& operator=(Three&& other) noexcept;

    Three& operator+=(const Three& other);
    Three& operator-=(const Three& other);

    bool operator==(const Three& other) const;
    bool operator!=(const Three& other) const;
    bool operator<(const Three& other) const;
    bool operator>(const Three& other) const;

    std::string toString() const;
};

#endif // THREE_H