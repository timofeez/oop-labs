#include <gtest/gtest.h>
#include "three.h"

TEST(ThreeTest, Addition) {
    Three three1("120");
    Three three2("100");

    three1 += three2;

    std::string result = three1.toString();
    ASSERT_TRUE(result == "220");  
}

TEST(ThreeTest, Subtraction) {
    Three three1("220");
    Three three2("220");

    three1 -= three2;

    std::string result = three1.toString();
    ASSERT_TRUE(result == "0");  
}

TEST(ThreeTest, ComparisonEqual) {
    Three three1("221");
    Three three2("221");

    ASSERT_TRUE(three1 == three2);  
}

TEST(ThreeTest, ComparisonNotEqual) {
    Three three1("221");
    Three three2("100");

    ASSERT_TRUE(three1 != three2);  
}

TEST(ThreeTest, ComparisonLess) {
    Three three1("102");
    Three three2("220");

    ASSERT_TRUE(three1 < three2);  
}

TEST(ThreeTest, ComparisonGreater) {
    Three three1("221");
    Three three2("102");

    ASSERT_TRUE(three1 > three2);  
}

TEST(ThreeTest, AddingWithZero) {
    Three three1("221");
    Three threeZero("0");

    three1 += threeZero;

    std::string result = three1.toString();
    ASSERT_TRUE(result == "221"); 
}

TEST(ThreeTest, SubtractingFromZero) {
    Three threeZero("0");
    Three threeLarge("1");

    try {
        threeZero -= threeLarge;
    } catch (const std::runtime_error& e) {
        std::string result = e.what();
        ASSERT_TRUE(result == "Отрицательный результат!");
    }
}

TEST(ThreeTest, ComplexAddition) {
    Three three1("122");
    Three three2("201");

    three1 += three2;

    std::string result = three1.toString();
    ASSERT_TRUE(result == "1100");  
}

TEST(ThreeTest, ComplexSubtraction) {
    Three three1("2102");
    Three three2("201");

    three1 -= three2;

    std::string result = three1.toString();
    ASSERT_TRUE(result == "1201");  
}
