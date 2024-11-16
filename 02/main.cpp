#include <iostream>
#include <limits>
#include "three.h"

int main() {
    Three* first_number = nullptr;
    Three* second_number = nullptr;
    std::cout << "Type 'help' to get info" << std::endl;

    while (true) {
        std::cout << "\nthree> ";
        std::string input;
        std::cin >> input;

        if (input == "exit") {
            delete first_number;
            delete second_number;
            return 0;
        }

        else if (input == "three1" || input == "three2") {
            std::cout << "Введите троичное число: ";    
            std::string inp;
            std::cin >> inp;
            
            try {
                if (input == "three1")
                    first_number = new Three(inp);
                else
                    second_number = new Three(inp);
            } catch (const std::invalid_argument& e) {
                std::cout << "Некорректный ввод!" << std::endl;
            }
        }

        else if (input == "+") {
            try {
                if (first_number && second_number) {
                    // Используем временную переменную для хранения результата сложения
                    Three result = *first_number;
                    result += *second_number;
                    std::cout << "Результат сложения: " << result.toString() << std::endl;
                } else {
                    std::cout << "Числа не определены!" << std::endl;
                }
            } catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << std::endl;
            }
        }

        else if (input == "-") {
            try {
                if (first_number && second_number) {
                    // Используем временную переменную для хранения результата вычитания
                    Three result = *first_number;
                    result -= *second_number;
                    std::cout << "Результат вычитания: " << result.toString() << std::endl;
                } else {
                    std::cout << "Числа не определены!" << std::endl;
                }
            } catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << std::endl;
            }
        }

        else if (input == ">" || input == "<" || input == "==" || input == "!=") {
            if (first_number && second_number) {
                bool result = false;
                if (input == ">") result = *first_number > *second_number;
                else if (input == "<") result = *first_number < *second_number;
                else if (input == "==") result = *first_number == *second_number;
                else if (input == "!=") result = *first_number != *second_number;

                std::cout << (result ? "true" : "false") << std::endl;
            } else {
                std::cout << "Числа не определены!" << std::endl;
            }
        }

        else if (input == "help") {
            std::cout << "three1/three2 : ввести первое/второе число в троичной форме" << std::endl;
            std::cout << "+/- : вывести результат сложения/вычитания чисел" << std::endl;
            std::cout << ">/</==/!= : вывести результат сравнения чисел" << std::endl;
            std::cout << "exit : выход" << std::endl;
        }

        else {
            std::cout << "Команда не найдена!" << std::endl;
        }
    }
}
