#include <gtest/gtest.h>

// Include any additional library here
#include<string>
#include<cmath>
 

// Include header files containing functions to be tested here
#include"../src/ballot.h"


// Add global information here (if needed)
class BallotTest : public ::testing::Test {
    virtual void SetUp() {
        in_line_1 = "1,2,3,4";
        ballot_1 = new Ballot(in_line_1, 0);

        in_line_2 = "4,3,2,1";
        ballot_2 = new Ballot(in_line_2, 1);

        ballot_3 = new Ballot();

        in_line_4 = ",1,2,";
        ballot_4 = new Ballot(in_line_4,3);
    }

    virtual void TearDown() {

    }

    public:
        Ballot* ballot_1;
        Ballot* ballot_2;
        Ballot* ballot_3;
        Ballot* ballot_4;
    
    private:
        std::string in_line_1;
        std::string in_line_2;
        std::string in_line_4;
};


/**
 * Write the tests here
 * Format as follows:
 * TEST(TestSuite, TestName) {
 *     // Write something here
 * }
 * 
 * Two common test methods:
 *    1. EXPECT_EQ(result returned from a function, actual result)
 *    2. ASSERT_DEATH(result returned from a function, error message to be displayed)
 * 
 * More information can be found here: http://google.github.io/googletest/primer.html
 * 
 */ 

TEST_F(BallotTest, TestBallotConstructor) {
    EXPECT_EQ(ballot_1->GetCurrentVote(), 0);
    EXPECT_EQ(ballot_2->GetCurrentVote(), 3);
    EXPECT_EQ(ballot_4->GetCurrentVote(), 1);
}

TEST_F(BallotTest, TestBallotDefaultConstructor) {
    EXPECT_EQ(ballot_3->GetCurrentVote(), -1);
}

TEST_F(BallotTest, TestGetID) {
    EXPECT_EQ(ballot_1->GetID(), 0);
    EXPECT_EQ(ballot_2->GetID(), 1);
    EXPECT_EQ(ballot_3->GetID(), -1);
    EXPECT_EQ(ballot_4->GetID(), 3);    
}

TEST_F(BallotTest, TestIncrement) {
    EXPECT_EQ(ballot_1->Increment(), 1);
    EXPECT_EQ(ballot_1->Increment(), 2);
    EXPECT_EQ(ballot_1->Increment(), 3);
    EXPECT_EQ(ballot_1->Increment(), -1);
    EXPECT_EQ(ballot_4->Increment(), 2);
    EXPECT_EQ(ballot_4->Increment(), -1);
}


// Thoughts
// Test ballot input - all entries filled, one entry filled
// Test Process...() - one candidate gets all votes


// Main function to rn all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}