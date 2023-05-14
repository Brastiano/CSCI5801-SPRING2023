#include <gtest/gtest.h>
#include <fstream>
#include "../src/party.h"
#include "../src/cpl.h"
#include "../src/election.h"

class CPLTest : public Election, public ::testing::Test {
	virtual void SetUp() {
		total_parties = 6;
		parties = "Democratic, Republican, New Wave, Reform, Green, Independent";
		candidates = "Foster, Volz, Pike\nGreen, Xu, Wang\nJacks, Rosen\nMcClure, Berg\nZheng, Melvin\nPeters";
		total_seats = 3;
		total_ballots = 9;
		Election::SetFilePaths("../testing/cpl_input_test_0.csv", "abc.txt");
		cpl = new CPL(total_parties, parties, candidates, total_seats, total_ballots);
	}

	virtual void TearDown() {
		delete cpl;
	}

	public:
		CPL* cpl;
		int total_parties;
		std::string parties;
		std::string candidates;
		int total_seats;
		int total_ballots;
};

TEST_F(CPLTest, TestInitializeParty) {
	// Read the ballots from within CPL
	cpl->UpdateBallots();

	// Pass necessary information to the Party instance
	cpl->InitializeParty();

	// Check if the Party instance actually read the store the inforamtion
	EXPECT_EQ(cpl->GetParties()->GetPartyName(0), "Democratic");
}

// Main function to run all the tests above
int main(int argc, char **argv) {
  	::testing::InitGoogleTest(&argc, argv);
 	return RUN_ALL_TESTS();
}