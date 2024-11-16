#include "three.h"
#include <algorithm>
#include <iostream>

Array::Array() : _digits(nullptr), _capacity(0), _size(0) {}

Array::Array(size_t size) 
    : _digits(new unsigned char[size]()), _capacity(size), _size(size) {}

Array::Array(const std::initializer_list<unsigned char>& digits)
    : _capacity(digits.size()), _size(digits.size()), _digits(new unsigned char[digits.size()]) {
    std::copy(digits.begin(), digits.end(), _digits);
}

Array::Array(const Array& other) 
    : _capacity(other._capacity), _size(other._size), _digits(new unsigned char[other._capacity]) {
    std::copy(other._digits, other._digits + _size, _digits);
}

Array::Array(Array&& other) noexcept 
    : _digits(other._digits), _capacity(other._capacity), _size(other._size) {
    other._digits = nullptr;
    other._capacity = 0;
    other._size = 0;
}

Array::~Array() noexcept {
    delete[] _digits;
}

Array& Array::operator=(const Array& other) {
    if (this == &other) return *this;
    if (_capacity != other._capacity) {
        delete[] _digits;
        _digits = new unsigned char[other._capacity];
        _capacity = other._capacity;
    }
    _size = other._size;
    std::copy(other._digits, other._digits + _size, _digits);
    return *this;
}

Array& Array::operator=(Array&& other) noexcept {
    if (this == &other) return *this;
    delete[] _digits;
    _digits = other._digits;
    _capacity = other._capacity;
    _size = other._size;
    other._digits = nullptr;
    other._capacity = 0;
    other._size = 0;
    return *this;
}

size_t Array::size() const {
    return _size;
}

unsigned char& Array::operator[](size_t index) {
    if (index >= _size) throw std::out_of_range("Индекс вне диапазона");
    return _digits[index];
}

const unsigned char& Array::operator[](size_t index) const {
    if (index >= _size) throw std::out_of_range("Индекс вне диапазона");
    return _digits[index];
}

Array& Array::operator+=(const Array& other) {
    size_t maxSize = std::max(_size, other._size);
    unsigned char* newDigits = new unsigned char[maxSize + 1]();
    int carry = 0;

    for (size_t i = 0; i < maxSize; ++i) {
        int sum = carry;
        if (i < _size) {
            sum += _digits[i];
        }
        if (i < other._size) {
            sum += other._digits[i];
        }
        newDigits[i] = sum % 3;
        carry = sum / 3;
    }

    if (carry > 0) {
        newDigits[maxSize] = carry;
        maxSize++;
    }

    delete[] _digits;
    _digits = newDigits;
    _size = maxSize;
    _capacity = maxSize;

    trimLeadingZeros();
    return *this;
}

Array& Array::operator-=(const Array& other) {
    if (*this < other) throw std::runtime_error("Отрицательный результат!");

    int borrow = 0;
    for (size_t i = 0; i < _size; ++i) {
        int diff = _digits[i] - (i < other._size ? other._digits[i] : 0) - borrow;
        if (diff < 0) {
            diff += 3;
            borrow = 1;
        } else {
            borrow = 0;
        }
        _digits[i] = diff;
    }

    trimLeadingZeros();
    return *this;
}

bool Array::operator==(const Array& other) const {
    if (_size != other._size) return false;
    for (size_t i = 0; i < _size; ++i) {
        if (_digits[i] != other._digits[i]) return false;
    }
    return true;
}

bool Array::operator!=(const Array& other) const {
    return !(*this == other);
}

bool Array::operator<(const Array& other) const {
    if (_size != other._size) {
        return _size < other._size;
    }
    for (size_t i = _size; i > 0; --i) {
        if (_digits[i - 1] < other._digits[i - 1]) return true;
        if (_digits[i - 1] > other._digits[i - 1]) return false;
    }
    return false;
}

bool Array::operator>(const Array& other) const {
    return other < *this;
}

void Array::trimLeadingZeros() {
    while (_size > 1 && _digits[_size - 1] == 0) {
        --_size;
    }
}

void Array::resize(size_t newSize) {
    if (newSize > _capacity) {
        unsigned char* newDigits = new unsigned char[newSize]();
        std::copy(_digits, _digits + _size, newDigits);
        delete[] _digits;
        _digits = newDigits;
        _capacity = newSize;
    }
    _size = newSize;
}

Three::Three() : Array() {}

Three::Three(const std::string& threeStr) : Array(threeStr.size()) {
    for (size_t i = 0; i < threeStr.size(); ++i) {
        if (threeStr[i] < '0' || threeStr[i] > '2') {
            throw std::invalid_argument("Недопустимый символ в троичной строке");
        }
        _digits[threeStr.size() - 1 - i] = threeStr[i] - '0';
    }
}

Three::Three(const Three& other) : Array(other) {}

Three::Three(Three&& other) noexcept : Array(std::move(other)) {}

Three::~Three() noexcept {}

Three& Three::operator=(const Three& other) {
    Array::operator=(other);
    return *this;
}

Three& Three::operator=(Three&& other) noexcept {
    Array::operator=(std::move(other));
    return *this;
}

Three& Three::operator+=(const Three& other) {
    Array::normalizeSize(*this, const_cast<Three&>(other));
    Array::operator+=(other);
    return *this;
}

Three& Three::operator-=(const Three& other) {
    Array::normalizeSize(*this, const_cast<Three&>(other));
    Array::operator-=(other);
    return *this;
}

bool Three::operator==(const Three& other) const {
    return Array::operator==(other);
}

bool Three::operator!=(const Three& other) const {
    return Array::operator!=(other);
}

bool Three::operator<(const Three& other) const {
    return Array::operator<(other);
}

bool Three::operator>(const Three& other) const {
    return Array::operator>(other);
}

std::string Three::toString() const {
    std::string result;
    for (size_t i = 0; i < _size; ++i) {
        result += _digits[i] + '0';
    }
    std::reverse(result.begin(), result.end());
    return result;
}

void Array::normalizeSize(Array& a, Array& b) {
    size_t maxSize = std::max(a.size(), b.size());
    a.resize(maxSize);
    b.resize(maxSize);
}
