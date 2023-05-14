#include <gtest/gtest.h>

// Include any additional library here
#include<string>
#include<cmath>
#include<fstream>
 

// Include header files containing functions to be tested here
#include"../src/ir.h"
#include"../src/candidate.h"


// Add global information here (if needed)
class ResultsTest : public ::testing::Test {
    virtual void SetUp() {
        cand_1 = new Candidate("John", "R");
    }

    virtual void TearDown() {
    }

    public:
        Candidate* cand_1;
    
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

TEST_F(ResultsTest, TestCandidateConstructor) {
    EXPECT_EQ(cand_1->name, "John");
    EXPECT_EQ(cand_1->party, "R");
    EXPECT_EQ(cand_1->GetVoteCount(), 0);
}

TEST_F(ResultsTest, TestAssignBallot) {
    Ballot* temp = new Ballot("1,2",0);
    cand_1->AssignBallot(temp);
    temp = new Ballot("1,2",1);
    cand_1->AssignBallot(temp);
    temp = new Ballot("1,",2);
    cand_1->AssignBallot(temp);

    EXPECT_EQ(cand_1->GetVoteCount(), 3);
}

TEST_F(ResultsTest, TestInitialChange) {
    EXPECT_EQ(cand_1->GetPrevVoteCount(), 0);
    cand_1->SetPrevVoteCount();
}

TEST_F(ResultsTest, TestRemoveReAssign) {
    Ballot* temp;
    temp = cand_1->RemoveBallot();
    EXPECT_EQ(temp->GetID(), 2);
    EXPECT_EQ(cand_1->GetVoteCount(), 2);
    EXPECT_EQ(cand_1->GetPrevVoteCount(), 3);
}

// Thoughts
// Test ballot input - all entries filled, one entry filled
// Test Process...() - one candidate gets all votes


// Main function to rn all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}