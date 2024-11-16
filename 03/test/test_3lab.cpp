#include "lab3.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(FigureTest, ArrayTotalArea) {
    Array array(10);
    
    Triangle* triangle = new Triangle();
    Square* square = new Square();
    Rectangle* rectangle = new Rectangle();

    std::istringstream is1("0 0 4 0 2 3");
    std::istringstream is2("0 0 4");
    std::istringstream is3("0 0 4 2");

    is1 >> *triangle;
    is2 >> *square;
    is3 >> *rectangle;

    array.addFigure(triangle);
    array.addFigure(square);
    array.addFigure(rectangle);

    double totalArea = array.totalArea();
    
    ASSERT_EQ(totalArea, 30);
}

TEST(FigureTest, ArrayTotalAreaWithDeleteElement) {
    Array array(10);

    Triangle* triangle = new Triangle();
    Square* square = new Square();
    Rectangle* rectangle = new Rectangle();

    std::istringstream is1("0 0 4 0 2 3");
    std::istringstream is2("0 0 4");
    std::istringstream is3("0 0 4 2");

    is1 >> *triangle;
    is2 >> *square;
    is3 >> *rectangle;

    array.addFigure(triangle);
    array.addFigure(square);
    array.addFigure(rectangle);
    
    array.removeFigure(1);

    double totalArea = array.totalArea();

    ASSERT_EQ(totalArea, 14);
}

TEST(FigureTest, SquareAssignment) {
    Square* square1 = new Square();
    Square* square2 = new Square();
    
    *square1 = *square2;
    ASSERT_TRUE(*square1 == *square2);
}


TEST(FigureTest, TriangleOutputStream) {
    Triangle* triangle = new Triangle();
    std::ostringstream os;
    os << *triangle;
    std::string expectedOutput = "Triangle: ((0, 0), (0, 0), (0, 0))";
    ASSERT_EQ(os.str(), expectedOutput);
}

TEST(FigureTest, SquareInputStream) {
    Square* square = new Square();
    std::istringstream is("0 0 4");
    is >> *square;
    double area = square->getArea();
    ASSERT_EQ(area, 16);
}

TEST(FigureTest, RectangleOperatorDouble) {
    Rectangle* rectangle = new Rectangle();
    std::istringstream is("0 0 4 2");
    is >> *rectangle;
    double value = static_cast<double>(*rectangle);
    ASSERT_EQ(value, 8);
}
