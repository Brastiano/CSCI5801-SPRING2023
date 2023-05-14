#include <gtest/gtest.h>

// Include any additional library here
#include<string>
#include<cmath>
#include<fstream>
 

// Include header files containing functions to be tested here
#include"../src/ir.h"
#include"../src/election.h"


// Add global information here (if needed)
class IRTest : public ::testing::Test {
    virtual void SetUp() {
        num_candidates = 4;
        candidates_string = "Rosen(D),Kleinberg(R),Chou(I),Royce(L)";
        num_ballots = 6;
        election_ = new IR(num_candidates, candidates_string, num_ballots);
        input_filepath = "testing/IR_input_test_1.csv";
        audit_filepath = "audit_test.txt";
    }

    virtual void TearDown() {
        delete election_;
    }

    public:
        IR* election_;
        std::string input_filepath;
        std::string audit_filepath;
    
    private:
        int num_candidates;
        int num_ballots;
        std::string candidates_string;

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

TEST_F(IRTest, TestElectionConstructor) {
    EXPECT_EQ(election_->GetCandidateName(0), "Rosen");
    EXPECT_EQ(election_->GetCandidateName(1), "Kleinberg");
    EXPECT_EQ(election_->GetCandidateName(2), "Chou");
    EXPECT_EQ(election_->GetCandidateName(3), "Royce");
}

TEST_F(IRTest, TestSetFilePaths) {
    election_->SetFilePaths(input_filepath, audit_filepath);
    EXPECT_EQ(election_->input_file.is_open(), true);
}

TEST_F(IRTest, TestInputBallots) {
    election_->InputBallots();
    EXPECT_EQ(election_->ValidCandidates(), 4);
}


// Thoughts
// Test ballot input - all entries filled, one entry filled
// Test Process...() - one candidate gets all votes


// Main function to rn all the tests above
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}