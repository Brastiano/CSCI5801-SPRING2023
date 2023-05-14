#include <gtest/gtest.h>
#include "../src/controller.h"
#include "../src/cli.h"
#include <vector>

TEST(MULTI_HEADER_CPL, two_files) {
    // Controller* controller = new Controller();
    Controller controller;
    Cli cli(controller);
    std::string arg_date = "unit_test_date";
    std::string arg_names[] = {"cpl_input_test_0.csv", "cpl_input_test_0.csv"};
    int n_files_ = 2;
    // std::cout << "!!!" << arg_names[0] << std::endl;
    controller.SetCli(cli, arg_date, arg_names, n_files_);
    int num_ballots = 0;
    std::vector<std::string> ballots_number = controller.GetBallotsNumber();
    for (int i = 0; i < ballots_number.size(); i++) {
        num_ballots += std::stoi(ballots_number.at(i));
    }
    EXPECT_EQ(18, num_ballots);
}

//input_file = 

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}