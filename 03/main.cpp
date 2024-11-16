#include "lab3.h"

int main() {
    Array array(10);  

    Triangle* triangle = new Triangle();
    Square* square = new Square();
    Rectangle* rectangle = new Rectangle();

    std::cout << "Введите координаты для треугольника (x1 y1 x2 y2 x3 y3): ";
    std::cin >> *triangle; 

    std::cout << "Введите координаты для квадрата (x y side): ";
    std::cin >> *square;

    std::cout << "Введите координаты для прямоугольника (x y width height): ";
    std::cin >> *rectangle;

    array.addFigure(triangle);
    array.addFigure(square);
    array.addFigure(rectangle);

    array.printFigures();

    std::cout << "Общая площадь фигур в массиве: " << array.totalArea() << std::endl;

    array.removeFigure(1);

    std::cout << "После удаления фигуры с индексом 1:" << std::endl;
    array.printFigures();
    return 0;
}