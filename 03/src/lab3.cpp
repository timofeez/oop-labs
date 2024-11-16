#include "lab3.h"

double Figure::getArea() const {
    if (!_areaCalculated) {
        _area = static_cast<double>(*this);
        _areaCalculated = true;
    }
    return _area;
}

double Figure::getFigureCenter() const {
    if (!_centerCalculated) {
        calculateFigureCenter();
        _centerCalculated = true;
    }
    return _centerX; 
}

Array::Array() : _capacity(10), _size(0) {
    _elements = new Figure*[_capacity];
}

Array::Array(size_t capacity) : _capacity(capacity), _size(0) {
    _elements = new Figure*[_capacity];
}

Array::~Array() noexcept {
    for (size_t i = 0; i < _size; ++i) {
        delete _elements[i];
    }
    delete[] _elements; 
}

void Array::addFigure(Figure* figure) {
    if (_size >= _capacity) {
        _capacity *= 2;
        Figure** newElements = new Figure*[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            newElements[i] = _elements[i];
        }
        delete[] _elements;
        _elements = newElements;
    }
    _elements[_size++] = figure; 
}

void Array::removeFigure(size_t index) {
    if (index < _size) {
        delete _elements[index]; 
        for (size_t i = index; i < _size - 1; ++i) {
            _elements[i] = _elements[i + 1]; 
        }
        --_size; 
    }
}

void Array::printFigures() const {
    for (size_t i = 0; i < _size; ++i) {
        std::cout << *_elements[i] << std::endl; 
    }
}

double Array::totalArea() const {
    double total = 0.0;
    for (size_t i = 0; i < _size; ++i) {
        total += _elements[i]->getArea(); 
    }
    return total;
}

void Triangle::calculateFigureCenter() const {
    _centerX = (__x1 + __x2 + __x3) / 3;
    _centerY = (__y1 + __y2 + __y3) / 3;
    _centerCalculated = true; 
}

Triangle::operator double() const {
    return 0.5 * abs(__x1 * (__y2 - __y3) + __x2 * (__y3 - __y1) + __x3 * (__y1 - __y2));
}

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        __x1 = other.__x1;
        __y1 = other.__y1;
        __x2 = other.__x2;
        __y2 = other.__y2;
        __x3 = other.__x3;
        __y3 = other.__y3;
    }
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other) noexcept {
    if (this != &other) {
        __x1 = other.__x1;
        __y1 = other.__y1;
        __x2 = other.__x2;
        __y2 = other.__y2;
        __x3 = other.__x3;
        __y3 = other.__y3;
    }
    return *this;
}

bool Triangle::operator==(const Triangle& other) const {
    return __x1 == other.__x1 && __y1 == other.__y1 &&
           __x2 == other.__x2 && __y2 == other.__y2 &&
           __x3 == other.__x3 && __y3 == other.__y3;
}

std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
    os << "Triangle: ((" << triangle.__x1 << ", " << triangle.__y1 << "), ("
       << triangle.__x2 << ", " << triangle.__y2 << "), ("
       << triangle.__x3 << ", " << triangle.__y3 << "))";
    return os;
}

std::istream& operator>>(std::istream& is, Triangle& triangle) {
    is >> triangle.__x1 >> triangle.__y1
       >> triangle.__x2 >> triangle.__y2
       >> triangle.__x3 >> triangle.__y3;
    return is;
}


void Square::calculateFigureCenter() const {
    _centerX = __x + __side / 2;
    _centerY = __y + __side / 2;
    _centerCalculated = true; 
}

Square::operator double() const {
    return __side * __side;
}

Square& Square::operator=(const Square& other) {
    if (this != &other) {
        __x = other.__x;
        __y = other.__y;
        __side = other.__side;
    }
    return *this;
}

Square& Square::operator=(Square&& other) noexcept {
    if (this != &other) {
        __x = other.__x;
        __y = other.__y;
        __side = other.__side;
    }
    return *this;
}

bool Square::operator==(const Square& other) const {
    return __x == other.__x && __y == other.__y && __side == other.__side;
}

std::ostream& operator<<(std::ostream& os, const Square& square) {
    os << "Square: (Center: (" << square.__x << ", " << square.__y << "), Side: " << square.__side << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Square& square) {
    is >> square.__x >> square.__y >> square.__side;
    return is;
}

void Rectangle::calculateFigureCenter() const {
    _centerX = __x + __width / 2;
    _centerY = __y + __height / 2;
    _centerCalculated = true; 
}

Rectangle::operator double() const {
    return __width * __height;
}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        __x = other.__x;
        __y = other.__y;
        __width = other.__width;
        __height = other.__height;
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        __x = other.__x;
        __y = other.__y;
        __width = other.__width;
        __height = other.__height;
    }
    return *this;
}

bool Rectangle::operator==(const Rectangle& other) const {
    return __x == other.__x && __y == other.__y &&
           __width == other.__width && __height == other.__height;
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle) {
    os << "Rectangle: (Center: (" << rectangle.__x << ", " << rectangle.__y << "), Width: " << rectangle.__width << ", Height: " << rectangle.__height << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Rectangle& rectangle) {
    is >> rectangle.__x >> rectangle.__y >> rectangle.__width >> rectangle.__height;
    return is;
}
