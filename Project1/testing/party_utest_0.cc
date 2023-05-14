#include <gtest/gtest.h>
#include "../src/party.h"
#include <vector>

class PartyTest : public ::testing::Test {
    virtual void SetUp() {
        num_parties = 6;
        parties_names = {"Democratic", "Republican", "New Wave", "Reform", "Green", "Independent"};
        p = new Party(num_parties);
    }

    virtual void TearDown() {
        delete p;
    }

    public:
        Party* p;
        int num_parties;
        std::vector<std::string> parties_names;
};

TEST_F(PartyTest, TestSetGetPartyName) {
    p->SetPartiesNames(parties_names);
    EXPECT_EQ(p->GetPartyName(0), "Democratic");
    EXPECT_EQ(p->GetPartyName(1), "Republican");
    EXPECT_EQ(p->GetPartyName(2), "New Wave");
    EXPECT_EQ(p->GetPartyName(3), "Reform");
    EXPECT_EQ(p->GetPartyName(4), "Green");
    EXPECT_EQ(p->GetPartyName(5), "Independent");
}

// Main function to run all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}