#include <gtest/gtest.h>
#include "../src/party.h"
#include <vector>

class PartyTest : public ::testing::Test {
    virtual void SetUp() {
        num_parties = 6;
        assigned_seats = {0, 0, 0, 0, 0, 0};
        p = new Party(num_parties);
        p->SetAssignedSeats(assigned_seats);
    }

    virtual void TearDown() {
        delete p;
    }

    public:
        Party* p;
        int num_parties;
        std::vector<int> assigned_seats;

};

TEST_F(PartyTest, TestSeats) {

    // Check intial assigned seats
    EXPECT_EQ(p->GetAssignedSeats(0), 0);
    EXPECT_EQ(p->GetAssignedSeats(1), 0);
    EXPECT_EQ(p->GetAssignedSeats(2), 0);
    EXPECT_EQ(p->GetAssignedSeats(3), 0);
    EXPECT_EQ(p->GetAssignedSeats(4), 0);
    EXPECT_EQ(p->GetAssignedSeats(5), 0);

    // Modify the number of seats assigned
    p->ModifySeats(0, 1);
    p->ModifySeats(1, 1);
    p->ModifySeats(2, 0);
    p->ModifySeats(3, 2);
    p->ModifySeats(4, 0);
    p->ModifySeats(5, 1);

    // Store the numbers after the whole number round
    p->StoreFirstRoundSeats();

    // Check if ModifySeats and StoreFirstRoundSeats functions is working
    EXPECT_EQ(p->GetFirstRoundSeats(0), 1);
    EXPECT_EQ(p->GetFirstRoundSeats(1), 1);
    EXPECT_EQ(p->GetFirstRoundSeats(2), 0);
    EXPECT_EQ(p->GetFirstRoundSeats(3), 2);
    EXPECT_EQ(p->GetFirstRoundSeats(4), 0);
    EXPECT_EQ(p->GetFirstRoundSeats(5), 1);
    
    // Check if ModifySeats and GetAssignedSeats functions is working
    EXPECT_EQ(p->GetAssignedSeats(0), 1);
    EXPECT_EQ(p->GetAssignedSeats(1), 1);
    EXPECT_EQ(p->GetAssignedSeats(2), 0);
    EXPECT_EQ(p->GetAssignedSeats(3), 2);
    EXPECT_EQ(p->GetAssignedSeats(4), 0);
    EXPECT_EQ(p->GetAssignedSeats(5), 1);

    // Modify the number of seats assigned once more
    p->ModifySeats(0, 1);
    p->ModifySeats(1, 1);
    p->ModifySeats(2, 0);
    p->ModifySeats(3, 2);
    p->ModifySeats(4, 0);
    p->ModifySeats(5, 1);

    // Make sure the number of seats after the first round is stored and unchanged
    EXPECT_EQ(p->GetFirstRoundSeats(0), 1);
    EXPECT_EQ(p->GetFirstRoundSeats(1), 1);
    EXPECT_EQ(p->GetFirstRoundSeats(2), 0);
    EXPECT_EQ(p->GetFirstRoundSeats(3), 2);
    EXPECT_EQ(p->GetFirstRoundSeats(4), 0);
    EXPECT_EQ(p->GetFirstRoundSeats(5), 1);
    
    // Check if ModifySeats and GetAssignedSeats functions is working
    EXPECT_EQ(p->GetAssignedSeats(0), 2);
    EXPECT_EQ(p->GetAssignedSeats(1), 2);
    EXPECT_EQ(p->GetAssignedSeats(2), 0);
    EXPECT_EQ(p->GetAssignedSeats(3), 4);
    EXPECT_EQ(p->GetAssignedSeats(4), 0);
    EXPECT_EQ(p->GetAssignedSeats(5), 2);
}

// Main function to run all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}