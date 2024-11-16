#ifndef LAB3_H
#define LAB3_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

class Figure {
protected:
    mutable double _area;
    mutable bool _areaCalculated;
    mutable double _centerX, _centerY;
    mutable bool _centerCalculated;

public:
    Figure() : _area(0), _areaCalculated(false), _centerX(0), _centerY(0), _centerCalculated(false) {}
    double getArea() const;
    double getFigureCenter() const;

    virtual void calculateFigureCenter() const = 0;
    virtual operator double() const = 0;

    virtual ~Figure() {}
};

class Array {
protected:
    Figure** _elements;  
    size_t _capacity;   
    size_t _size;        

public:
    Array(); 
    Array(size_t capacity); 
    Array(const Array& other);
    Array(Array&& other) noexcept;
    virtual ~Array() noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    size_t size() const;

    void addFigure(Figure* figure);
    void removeFigure(size_t index);
    void printFigures() const;
    double totalArea() const;
};

class Triangle: public Figure {
private:
    double __x1, __x2, __x3, __y1, __y2, __y3;
public:
    Triangle(): __x1(0), __x2(0), __x3(0), __y1(0), __y2(0), __y3(0) {}

    void calculateFigureCenter() const override;
    operator double() const override;

    Triangle& operator=(const Triangle& other);
    Triangle& operator=(Triangle&& other) noexcept;
    bool operator==(const Triangle& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle);
    friend std::istream& operator>>(std::istream& is, Triangle& triangle);
};

class Square: public Figure {
private:
    double __x, __y, __side;
public:
    Square(): __x(0), __y(0), __side(0) {}

    void calculateFigureCenter() const override;
    operator double() const override;

    Square& operator=(const Square& other);
    Square& operator=(Square&& other) noexcept;
    bool operator==(const Square& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Square& square);
    friend std::istream& operator>>(std::istream& is, Square& square);
};

class Rectangle: public Figure {
private:
    double __x, __y, __width, __height;
public:
    Rectangle(): __x(0), __y(0), __width(0), __height(0) {}

    void calculateFigureCenter() const override;
    operator double() const override;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;
    bool operator==(const Rectangle& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle);
    friend std::istream& operator>>(std::istream& is, Rectangle& rectangle);
};

#endif
