#include <gtest/gtest.h>
#include "../src/party.h"
#include <vector>

class PartyTest : public ::testing::Test {
    virtual void SetUp() {
        num_parties = 6;
        parties_names = {"Democratic", "Republican", "New Wave", "Reform", "Green", "Independent"};
        candidates_names = {{"Foster", "Volz", "Pike"},
                            {"Green", "Xu", "Wang"},
                            {"Jacks", "Rosen"},
                            {"McClure", "Berg"},
                            {"Zheng", "Melvin"},
                            {"Peters"}};
        available_candidates = {3, 3, 2, 2, 2, 1};
        votes_amounts = {5, 7, 3, 4, 2, 1};
        assigned_seats = {0, 0, 0, 0, 0, 0};
        p = new Party(num_parties);
        p->SetPartiesNames(parties_names);
        p->SetCandidatesNames(candidates_names);
        p->SetAvailableCandidates(available_candidates);
        p->SetVotesAmounts(votes_amounts);
        p->SetAssignedSeats(assigned_seats);
        p->StoreFirstRoundSeats();
    }

    virtual void TearDown() {
        delete p;
    }

    public:
        Party* p;
        int num_parties;
        std::vector<std::string> parties_names;
        std::vector<std::vector<std::string>> candidates_names;
        std::vector<int> available_candidates;
        std::vector<int> votes_amounts;
        std::vector<int> assigned_seats;

};

TEST_F(PartyTest, TestSwapParties) {
    // Check the nformation of parties at two indexes before swapping
    EXPECT_EQ(p->GetPartyName(2), "New Wave");
    EXPECT_EQ(p->GetCandidateName(2, 0), "Jacks");
    EXPECT_EQ(p->GetCandidateName(2, 1), "Rosen");
    EXPECT_EQ(p->GetCandidatesCount(2), 2);
    EXPECT_EQ(p->GetAvailableCandidates(2), 2);
    EXPECT_EQ(p->GetVotesAmount(2), 3);
    
    EXPECT_EQ(p->GetPartyName(5), "Independent");
    EXPECT_EQ(p->GetCandidateName(5, 0), "Peters");
    EXPECT_EQ(p->GetCandidatesCount(5), 1);
    EXPECT_EQ(p->GetAvailableCandidates(5), 1);
    EXPECT_EQ(p->GetVotesAmount(5), 1);

    // Perform party swapping
    p->SwapParties(2, 5);

    // Check the information of parties at two indexes after swapping
    EXPECT_EQ(p->GetPartyName(5), "New Wave");
    EXPECT_EQ(p->GetCandidateName(5, 0), "Jacks");
    EXPECT_EQ(p->GetCandidateName(5, 1), "Rosen");
    EXPECT_EQ(p->GetCandidatesCount(5), 2);
    EXPECT_EQ(p->GetAvailableCandidates(5), 2);
    EXPECT_EQ(p->GetVotesAmount(5), 3);
    
    EXPECT_EQ(p->GetPartyName(2), "Independent");
    EXPECT_EQ(p->GetCandidateName(2, 0), "Peters");
    EXPECT_EQ(p->GetCandidatesCount(2), 1);
    EXPECT_EQ(p->GetAvailableCandidates(2), 1);
    EXPECT_EQ(p->GetVotesAmount(2), 1);
}

// Main function to run all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}