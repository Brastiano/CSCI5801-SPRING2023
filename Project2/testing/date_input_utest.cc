#include <gtest/gtest.h>
#include "../src/controller.h"

TEST(DateTest, DateWorking) {
    std::string date_correct = "04_19_2023";
    Controller controller;
    EXPECT_EQ(date_correct, controller.HandleDateString(date_correct));
}

TEST(DateTest, DatePeriods) {
    std::string date_correct = "04_19_2023";
    std::string date = "04.19.2023";
    Controller controller;
    EXPECT_EQ(date_correct, controller.HandleDateString(date));
}

TEST(DateTest, DateSlashes) {
    std::string date_correct = "04_19_2023";
    std::string date = "04/19/2023";
    Controller controller;
    EXPECT_EQ(date_correct, controller.HandleDateString(date));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}