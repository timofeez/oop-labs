#include <iostream>
#include "include/convertTo24HourFormat.h"

int main() {
    int hour, minute;
    std::string period;

    std::cout << "Введите количество часов: " << std::endl;
    std::cin >> hour;

    std::cout << "Введите количество минут: " << std::endl;
    std::cin >> minute;

    std::cout << "Введите период времени (am/pm): " << std::endl;
    std::cin >> period;

    std::string result = convertTo24HourFormat(hour, minute, period);

    std::cout << result << std::endl;

    return 0;
}