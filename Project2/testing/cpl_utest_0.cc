#include <gtest/gtest.h>
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

TEST_F(CPLTest, TestConstructor) {
	EXPECT_EQ(cpl == NULL, true);
	cpl = new CPL(total_parties, parties, candidates, total_seats, total_ballots);
	EXPECT_EQ(cpl == NULL, false);
}

// Main function to run all the tests above
int main(int argc, char **argv) {
  	::testing::InitGoogleTest(&argc, argv);
 	return RUN_ALL_TESTS();
}