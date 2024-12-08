#include "utils.h"
#include <random>
#include <cmath>

int getRandomNumber(int min, int max) {
    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}


bool canAttack(const std::string& attackerType, const std::string& targetType, double distance) {
    if (attackerType == "Squirrel") {
        if (targetType == "Druid" || targetType == "Werewolf") {
            return distance <= 5;
        }
    }
    else if (attackerType == "Werewolf") {
        if (targetType == "Druid") {
            return distance <= 5;
        }
    }
    return false;
}
