#include "../include/convertTo24HourFormat.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

std::string convertTo24HourFormat(int hour, int minute, std::string period) {
    if (period == "am") {
        if (hour == 12) {
            hour = 0;
        }
    } else if (period == "pm") {
        if (hour != 12) {
            hour += 12;
        }
    }

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour
        << std::setw(2) << std::setfill('0') << minute;

    return oss.str();
}