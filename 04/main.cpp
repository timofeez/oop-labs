#include <limits>
#include <iostream>
#include <memory>
#include "rectangle.h"
#include "square.h"
#include "triangle.h"
#include "array.h"
#include "figure.h"    

int main() {
    using type = float;
    auto figures = std::make_shared<Array<std::shared_ptr<figure<type>>>>();

    std::cout << "Type 'help' to get info" << std::endl;

    while (true) {
        std::cout << "\nfigure> ";
        std::string input;
        std::cin >> input;

        if (input == "exit")
            return 0;

        if (input == "input") {
            int param;
            std::cout << "Выберите тип фигуры (1 - прямоугольник, 2 - квадрат, 3 - треугольник): ";
            std::cin >> param;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод!" << std::endl;
            }
            else if (param == 1) {
                auto rectangle = std::make_shared<rectangle<type>>();
                try {
                    std::cin >> *rectangle;
                    figures->add(rectangle);
                } catch (const std::invalid_argument&) {
                    std::cout << "Введённая фигура не является прямоугольником!" << std::endl;
                }
            }
            else if (param == 2) {
                auto square = std::make_shared<square<type>>();
                try {
                    std::cin >> *square;
                    figures->add(square);
                } catch (const std::invalid_argument&) {
                    std::cout << "Введённая фигура не является квадратом!" << std::endl;
                }
            }
            else if (param == 3) {
                auto triangle = std::make_shared<triangle<type>>();
                try {
                    std::cin >> *triangle;
                    figures->add(triangle);
                } catch (const std::invalid_argument&) {
                    std::cout << "Введённая фигура не является треугольником!" << std::endl;
                }
            }
            else {
                std::cout << "Некорректный ввод!" << std::endl;
            }
        }
        else if (input == "info") {
            if (figures->size == 0)
                std::cout << "Список фигур пуст!" << std::endl;
            else {
                for (size_t i = 0; i < figures->size; ++i)
                    std::cout << *(*figures)[i] << " Площадь: " << (*figures)[i]->area() << " Центр: "
                        << (*figures)[i]->get_center() << std::endl;
            }
        }
        else if (input == "square") {
            if (figures->size == 0)
                std::cout << 0 << std::endl;
            else {
                double total_square = 0.0;
                for (size_t i = 0; i < figures->size; ++i)
                    total_square += (*figures)[i]->area();
                std::cout << total_square << std::endl;
            }
        }
        else if (input == "pop") {
            int index;
            std::cout << "Введите индекс удаляемой фигуры: ";
            std::cin >> index;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод!" << std::endl;
            } else {
                try {
                    auto popped = figures->pop(index);
                    std::cout << *popped << " удалена" << std::endl;
                } catch (const std::out_of_range&) {
                    std::cout << "Элемент с указанным индексом не существует!" << std::endl;
                }
            }
        }
        else if (input == "help") {
            std::cout << "input : ввести фигуру" << std::endl;
            std::cout << "info : вывести информацию о всех фигурах" << std::endl;
            std::cout << "square : вывести суммарную площадь фигур" << std::endl;
            std::cout << "pop : удалить фигуру по индексу" << std::endl;
            std::cout << "exit : выход" << std::endl;
        }
        else {
            std::cout << "Команда не найдена!" << std::endl;
        }
    }
}
