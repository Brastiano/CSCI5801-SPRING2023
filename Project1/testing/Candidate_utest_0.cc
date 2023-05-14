#include <gtest/gtest.h>

// Include any additional library here
#include<string>
#include<cmath>
 

// Include header files containing functions to be tested here
#include"../src/candidate.h"


// Add global information here (if needed)
class CandidateTest : public ::testing::Test {
    virtual void SetUp() {
        cand_1 = new Candidate("John", "R");
        cand_2 = new Candidate();
        candidates = new Candidate[2];
    }

    virtual void TearDown() {

    }

    public:
        Candidate* candidates;
        Candidate* cand_1;
        Candidate* cand_2;
    private:
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

TEST_F(CandidateTest, TestCandidateConstructor) {
    EXPECT_EQ(cand_1->name, "John");
    EXPECT_EQ(cand_1->party, "R");
    EXPECT_EQ(cand_1->GetVoteCount(), 0);
}

TEST_F(CandidateTest, TestCandidateDefaultConstructor) {
    EXPECT_EQ(cand_2->name, "");
    EXPECT_EQ(cand_2->party, "");
    EXPECT_EQ(cand_2->GetVoteCount(), 0);
}

TEST_F(CandidateTest, TestCandidateInit) {
    candidates[0].Init("John","R");
    candidates[1].Init("Bernie", "D");
    EXPECT_EQ(candidates[0].name, "John");
    EXPECT_EQ(candidates[0].party, "R");
    EXPECT_EQ(candidates[1].name, "Bernie");
    EXPECT_EQ(candidates[1].party, "D");
}

TEST_F(CandidateTest, TestAssignBallot) {
    Ballot* temp = new Ballot("1,2",0);
    candidates[temp->GetCurrentVote()].AssignBallot(temp);
    temp = new Ballot("2,1",1);
    candidates[temp->GetCurrentVote()].AssignBallot(temp);
    temp = new Ballot(",1",2);
    candidates[temp->GetCurrentVote()].AssignBallot(temp);

    EXPECT_EQ(candidates[0].GetVoteCount(), 1);
    EXPECT_EQ(candidates[1].GetVoteCount(), 2);
}

TEST_F(CandidateTest, TestRemoveReAssign) {
    Ballot* temp;
    temp = candidates[0].RemoveBallot();
    EXPECT_EQ(temp->GetID(), 0);
    candidates[temp->GetCurrentVote()].AssignBallot(temp);
    EXPECT_EQ(candidates[0].GetVoteCount(), 0);
    EXPECT_EQ(candidates[1].GetVoteCount(), 3);
}

TEST_F(CandidateTest, TestGetVoteIDs) {
    EXPECT_EQ(candidates[0].GetVoteIDs(), "");
    EXPECT_EQ(candidates[1].GetVoteIDs(), "1,2,0");
}




// Thoughts
// Test ballot input - all entries filled, one entry filled
// Test Process...() - one candidate gets all votes


// Main function to rn all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}