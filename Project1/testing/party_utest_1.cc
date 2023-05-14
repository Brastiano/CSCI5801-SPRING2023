#include <gtest/gtest.h>
#include "../src/party.h"
#include <vector>

class PartyTest : public ::testing::Test {
    virtual void SetUp() {
        num_parties = 6;
        candidates_names = {{"Foster", "Volz", "Pike"},
                            {"Green", "Xu", "Wang"},
                            {"Jacks", "Rosen"},
                            {"McClure", "Berg"},
                            {"Zheng", "Melvin"},
                            {"Peters"}};
        p = new Party(num_parties);
    }

    virtual void TearDown() {
        delete p;
    }

    public:
        Party* p;
        int num_parties;
        std::vector<std::vector<std::string>> candidates_names;
};

TEST_F(PartyTest, TestSetGetCandidateName) {
    p->SetCandidatesNames(candidates_names);
    EXPECT_EQ(p->GetCandidateName(0, 0), "Foster");
    EXPECT_EQ(p->GetCandidateName(0, 1), "Volz");
    EXPECT_EQ(p->GetCandidateName(0, 2), "Pike");
    EXPECT_EQ(p->GetCandidateName(1, 0), "Green");
    EXPECT_EQ(p->GetCandidateName(1, 1), "Xu");
    EXPECT_EQ(p->GetCandidateName(1, 2), "Wang");
    EXPECT_EQ(p->GetCandidateName(2, 0), "Jacks");
    EXPECT_EQ(p->GetCandidateName(2, 1), "Rosen");
    EXPECT_EQ(p->GetCandidateName(3, 0), "McClure");
    EXPECT_EQ(p->GetCandidateName(3, 1), "Berg");
    EXPECT_EQ(p->GetCandidateName(4, 0), "Zheng");
    EXPECT_EQ(p->GetCandidateName(4, 1), "Melvin");
    EXPECT_EQ(p->GetCandidateName(5, 0), "Peters");
}

// Main function to run all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}