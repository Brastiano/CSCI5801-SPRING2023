#include <gtest/gtest.h>
#include "../src/party.h"
#include <vector>

class PartyTest : public ::testing::Test {
    virtual void SetUp() {
        num_parties = 6;
        votes_amounts = {5, 7, 3, 4, 2, 1};
        p = new Party(num_parties);
    }

    virtual void TearDown() {
        delete p;
    }

    public:
        Party* p;
        int num_parties;
        std::vector<int> votes_amounts;

};

TEST_F(PartyTest, TestSetGetVotesAmount) {
    p->SetVotesAmounts(votes_amounts);

    EXPECT_EQ(p->GetVotesAmount(0), 5);
    EXPECT_EQ(p->GetVotesAmount(1), 7);
    EXPECT_EQ(p->GetVotesAmount(2), 3);
    EXPECT_EQ(p->GetVotesAmount(3), 4);
    EXPECT_EQ(p->GetVotesAmount(4), 2);
    EXPECT_EQ(p->GetVotesAmount(5), 1);
    
    EXPECT_EQ(p->GetInitialVotesAmount(0), 5);
    EXPECT_EQ(p->GetInitialVotesAmount(1), 7);
    EXPECT_EQ(p->GetInitialVotesAmount(2), 3);
    EXPECT_EQ(p->GetInitialVotesAmount(3), 4);
    EXPECT_EQ(p->GetInitialVotesAmount(4), 2);
    EXPECT_EQ(p->GetInitialVotesAmount(5), 1);
}

// Main function to run all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}