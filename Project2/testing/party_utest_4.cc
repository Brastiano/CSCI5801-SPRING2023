#include <gtest/gtest.h>
#include "../src/party.h"
#include <vector>

class PartyTest : public ::testing::Test {
    virtual void SetUp() {
        num_parties = 6;
        assigned_seats = {0, 0, 0, 0, 0, 0};
        p = new Party(num_parties);
    }

    virtual void TearDown() {
        delete p;
    }

    public:
        Party* p;
        int num_parties;
        std::vector<int> assigned_seats;

};

TEST_F(PartyTest, TestGetAssignedSeats) {
    p->SetAssignedSeats(assigned_seats);    
    EXPECT_EQ(p->GetAssignedSeats(0), 0);
    EXPECT_EQ(p->GetAssignedSeats(1), 0);
    EXPECT_EQ(p->GetAssignedSeats(2), 0);
    EXPECT_EQ(p->GetAssignedSeats(3), 0);
    EXPECT_EQ(p->GetAssignedSeats(4), 0);
    EXPECT_EQ(p->GetAssignedSeats(5), 0);
}

// Main function to run all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}