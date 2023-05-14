#include <gtest/gtest.h>
#include "../src/party.h"
#include <vector>

class PartyTest : public ::testing::Test {
    virtual void SetUp() {
        num_parties = 6;
        available_candidates = {3, 3, 2, 2, 2, 1};
        p = new Party(num_parties);        
        p->SetAvailableCandidates(available_candidates);
    }

    virtual void TearDown() {
        delete p;
    }

    public:
        Party* p;
        int num_parties;
        std::vector<int> available_candidates;

};

TEST_F(PartyTest, TestCandidates) {
    // Test number of candidates each party has  
    EXPECT_EQ(p->GetCandidatesCount(0), 3);
    EXPECT_EQ(p->GetCandidatesCount(1), 3);
    EXPECT_EQ(p->GetCandidatesCount(2), 2);
    EXPECT_EQ(p->GetCandidatesCount(3), 2);
    EXPECT_EQ(p->GetCandidatesCount(4), 2);
    EXPECT_EQ(p->GetCandidatesCount(5), 1);
    
    // Test initial number of available candidates each party has
    EXPECT_EQ(p->GetAvailableCandidates(0), 3);
    EXPECT_EQ(p->GetAvailableCandidates(1), 3);
    EXPECT_EQ(p->GetAvailableCandidates(2), 2);
    EXPECT_EQ(p->GetAvailableCandidates(3), 2);
    EXPECT_EQ(p->GetAvailableCandidates(4), 2);
    EXPECT_EQ(p->GetAvailableCandidates(5), 1);

    // Modify the number of available candidates
    p->ModifyAvailableCandidates(0, -1);
    p->ModifyAvailableCandidates(1, -0);
    p->ModifyAvailableCandidates(2, -1);
    p->ModifyAvailableCandidates(3, -2);
    p->ModifyAvailableCandidates(4, -1);
    p->ModifyAvailableCandidates(5, -0);

    // Make sure the number of candidates each party has does not change
    EXPECT_EQ(p->GetCandidatesCount(0), 3);
    EXPECT_EQ(p->GetCandidatesCount(1), 3);
    EXPECT_EQ(p->GetCandidatesCount(2), 2);
    EXPECT_EQ(p->GetCandidatesCount(3), 2);
    EXPECT_EQ(p->GetCandidatesCount(4), 2);
    EXPECT_EQ(p->GetCandidatesCount(5), 1);
    
    // Check if number of available candidates each party has is changed
    EXPECT_EQ(p->GetAvailableCandidates(0), 2);
    EXPECT_EQ(p->GetAvailableCandidates(1), 3);
    EXPECT_EQ(p->GetAvailableCandidates(2), 1);
    EXPECT_EQ(p->GetAvailableCandidates(3), 0);
    EXPECT_EQ(p->GetAvailableCandidates(4), 1);
    EXPECT_EQ(p->GetAvailableCandidates(5), 1);
}

// Main function to run all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}