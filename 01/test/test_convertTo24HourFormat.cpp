#include <gtest/gtest.h>
#include "../include/convertTo24HourFormat.h"

TEST(test_01, basic_test_set) {
    int hour = 12;
    int minute = 0;
    std::string period = "am";
    std::string result = convertTo24HourFormat(hour, minute, period);
    ASSERT_EQ(result, "0000");
}

TEST(test_02, basic_test_set) {
    int hour = 12;
    int minute = 0;
    std::string period = "pm";
    std::string result = convertTo24HourFormat(hour, minute, period);
    ASSERT_EQ(result, "1200");
}

TEST(test_03, basic_test_set) {
    int hour = 1;
    int minute = 0;
    std::string period = "am";
    std::string result = convertTo24HourFormat(hour, minute, period);
    ASSERT_EQ(result, "0100");
}

TEST(test_04, basic_test_set) {
    int hour = 1;
    int minute = 0;
    std::string period = "pm";
    std::string result = convertTo24HourFormat(hour, minute, period);
    ASSERT_EQ(result, "1300");
}

TEST(test_05, basic_test_set) {
    int hour = 11;
    int minute = 59;
    std::string period = "pm";
    std::string result = convertTo24HourFormat(hour, minute, period);
    ASSERT_EQ(result, "2359");
}

TEST(test_06, basic_test_set) {
    int hour = 12;
    int minute = 45;
    std::string period = "am";
    std::string result = convertTo24HourFormat(hour, minute, period);
    ASSERT_EQ(result, "0045");
}

TEST(test_07, basic_test_set) {
    int hour = 5;
    int minute = 30;
    std::string period = "pm";
    std::string result = convertTo24HourFormat(hour, minute, period);
    ASSERT_EQ(result, "1730");
}

TEST(test_08, basic_test_set) {
    int hour = 9;
    int minute = 0;
    std::string period = "xx";
    std::string result = convertTo24HourFormat(hour, minute, period);
    ASSERT_EQ(result, "0900");
}

TEST(test_09, basic_test_set) {
    int hour = 12;
    int minute = 1;
    std::string period = "am";
    std::string result = convertTo24HourFormat(hour, minute, period);
    ASSERT_EQ(result, "0001");
}

TEST(test_10, basic_test_set) {
    int hour = 12;
    int minute = 1;
    std::string period = "pm";
    std::string result = convertTo24HourFormat(hour, minute, period);
    ASSERT_EQ(result, "1201");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
