#include <gtest/gtest.h>
#include "../src/party.h"
#include <vector>

class PartyTest : public ::testing::Test {
    virtual void SetUp() {
        num_parties = 6;
        votes_amounts = {5, 7, 3, 4, 2, 1};
        p = new Party(num_parties);
        p->SetVotesAmounts(votes_amounts);
    }

    virtual void TearDown() {
        delete p;
    }

    public:
        Party* p;
        int num_parties;
        std::vector<int> votes_amounts;

};

TEST_F(PartyTest, TestVotesAmount) {
    // Check intial votes amount
    EXPECT_EQ(p->GetInitialVotesAmount(0), 5);
    EXPECT_EQ(p->GetInitialVotesAmount(1), 7);
    EXPECT_EQ(p->GetInitialVotesAmount(2), 3);
    EXPECT_EQ(p->GetInitialVotesAmount(3), 4);
    EXPECT_EQ(p->GetInitialVotesAmount(4), 2);
    EXPECT_EQ(p->GetInitialVotesAmount(5), 1);
    
    EXPECT_EQ(p->GetVotesAmount(0), 5);
    EXPECT_EQ(p->GetVotesAmount(1), 7);
    EXPECT_EQ(p->GetVotesAmount(2), 3);
    EXPECT_EQ(p->GetVotesAmount(3), 4);
    EXPECT_EQ(p->GetVotesAmount(4), 2);
    EXPECT_EQ(p->GetVotesAmount(5), 1);
    
    // Modify the number of votes assigned
    p->ModifyVotes(0, -1);
    p->ModifyVotes(1, -1);
    p->ModifyVotes(2, 0);
    p->ModifyVotes(3, -2);
    p->ModifyVotes(4, 0);
    p->ModifyVotes(5, -1);

    // Make sure the number of initial votes does not change
    EXPECT_EQ(p->GetInitialVotesAmount(0), 5);
    EXPECT_EQ(p->GetInitialVotesAmount(1), 7);
    EXPECT_EQ(p->GetInitialVotesAmount(2), 3);
    EXPECT_EQ(p->GetInitialVotesAmount(3), 4);
    EXPECT_EQ(p->GetInitialVotesAmount(4), 2);
    EXPECT_EQ(p->GetInitialVotesAmount(5), 1);
    
    // Make sure the actual number of votes is deducted
    EXPECT_EQ(p->GetVotesAmount(0), 4);
    EXPECT_EQ(p->GetVotesAmount(1), 6);
    EXPECT_EQ(p->GetVotesAmount(2), 3);
    EXPECT_EQ(p->GetVotesAmount(3), 2);
    EXPECT_EQ(p->GetVotesAmount(4), 2);
    EXPECT_EQ(p->GetVotesAmount(5), 0);
}

// Main function to run all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}