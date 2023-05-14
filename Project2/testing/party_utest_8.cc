#include <gtest/gtest.h>
#include "../src/party.h"
#include <vector>

class PartyTest : public ::testing::Test {
    virtual void SetUp() {
        num_parties = 6;
        p = new Party(num_parties);
    }

    virtual void TearDown() {
        delete p;
    }

    public:
        Party* p;
        int num_parties;
};

TEST_F(PartyTest, TestChangeInSeats) {
    // Check intial number of changes in seats
    EXPECT_EQ(p->GetChangeInSeats(0), 0);
    EXPECT_EQ(p->GetChangeInSeats(1), 0);
    EXPECT_EQ(p->GetChangeInSeats(2), 0);
    EXPECT_EQ(p->GetChangeInSeats(3), 0);
    EXPECT_EQ(p->GetChangeInSeats(4), 0);
    EXPECT_EQ(p->GetChangeInSeats(5), 0);

    // Modify the number of changes in seats
    p->ModifyChangeInSeats(0, 0);
    p->ModifyChangeInSeats(1, 1);
    p->ModifyChangeInSeats(2, 2);
    p->ModifyChangeInSeats(3, 1);
    p->ModifyChangeInSeats(4, 1);
    p->ModifyChangeInSeats(5, 0);

    // Check if the number of changes in seats is changed
    EXPECT_EQ(p->GetChangeInSeats(0), 0);
    EXPECT_EQ(p->GetChangeInSeats(1), 1);
    EXPECT_EQ(p->GetChangeInSeats(2), 2);
    EXPECT_EQ(p->GetChangeInSeats(3), 1);
    EXPECT_EQ(p->GetChangeInSeats(4), 1);
    EXPECT_EQ(p->GetChangeInSeats(5), 0);
}

// Main function to run all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}