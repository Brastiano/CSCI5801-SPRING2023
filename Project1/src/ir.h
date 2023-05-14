/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Andrew Brevick
 * File name: ir.h
 * Description: Specific strategy of Election for processing IR election logic
 * @endcond
 */

#ifndef IR_H
#define IR_H

#include<string>
#include"election.h"
#include"candidate.h"
#include<cmath>


enum win_type_e
{
    majority,
    popular
};

/**
 * @brief Specific strategy implementation of Election class for processing IR election logic
 * 
 */
class IR : public Election
{
public:
    /**
     * @brief Construct a new IR object
     * 
     * @param n_cand 
     * @param all_cand 
     * @param n_ball
     */
    IR(int n_cand, std::string all_cand, int n_ball);

    /**
     * @brief Reallocate ballots from an eliminated canidate
     * 
     * @param idx_rm candidate index of the removed candidate
     */
    void Reallocate(int idx_rm);

    /**
     * @brief runs the entire election, from inputing ballots to outputting an audit file and results
     * 
     * @param results_top Summary of election results
     * @param results_table Tabulated results by candidate
     */
    void ProcessElection(std::string &results_top, std::string &results_table);

    /**
     * @brief reads ballot file line by line, creates Ballot objects, and assigns them to candidates
     * 
     */
    void InputBallots();

    /**
     * @brief Getter for candidate names
     * @return candidate name
     * @param candidate_index
     */
    std::string GetCandidateName(int candidate_index);

    /**
     * @brief Counts number of candidates who have votes and are thus still in the election
     * 
     * @return int 
     */
    int ValidCandidates();

private:
    /**
     * @brief Find the candidate with the minimum number of votes
     * @return int candidate index
     */
    int FindMin();

    /**
     * @brief resolve an election as a popular vote if no candidate reaches majority
     * 
     * @param idx1 index of one remaining candidate
     * @param idx2 index of second remaining candidate
     * @return int index of winner
     */
    int ResolvePopular(int idx1, int idx2);

    /**
     * @brief parses the header candidate line for the next candidate 
     * 
     * @param all_cand full header string
     * @return std::string candidate name and party "name (P)"
     */
    std::string GetNextCandidateName(std::string &all_cand);

    /**
     * @brief Splits a candidate string into their name and party
     * 
     * @param one_cand 
     * @param name 
     * @param party 
     */
    void ParseCandidateName(std::string one_cand, std::string &name, std::string &party);

    /**
     * @brief array of Candidate objects for storage and management of ballots
     * 
     */
    Candidate* candidates;

    /**
     * @brief object which provides a location to store dead ballots
     * 
     */
    Candidate* null_candidate;

    /**
     * @brief number of candidates in the election
     * 
     */
    int n_candidates;

    /**
     * @brief number of ballots in the ballot file
     * 
     */
    int n_ballots; 

    /**
     * @brief current count of number of candidates that are still active in the election
     * 
     */
    int valid_candidates; 

    /**
     * @brief Checks whether any candidate has acheived majority
     * 
     * @return int index of candidate with majority, -1 if not candidate is found
     */
    int CheckMajority();

    /**
     * @brief Finds the indexes of remaining candidates when only 2 remain
     * @param idx1 
     * @param idx2 
     */
    void FindRemainingCandidates(int &idx1, int &idx2);

    /**
     * @brief write the audit information that is contained in the input header
     */
    void WriteHeaderAudit();

    /**
     * @brief write the audit information for the current round
     * This include each candidates name, party, vote count, and then a listing of each ballot id assigned to them. 
     */
    void WriteRoundAudit();

    /**
     * @brief write the audit information for a reallocation of ballots
     * This includes the candidate index which is removed and whether a tie break was used
     * @param idx_min 
     */
    void WriteReallocationAudit(int idx_min);

    /**
     * @brief write the audit information for the election results
     * This includes winners and final vote tallies
     * @param win_type majority or popular vote
     */
    void WriteResultAudit(win_type_e win_type);

    /**
     * @brief Set the results display strings to pass to the user interface
     * 
     * @param results_top Summary of election results
     * @param results_table Tabulated results by candidate
     */
    void SetResultsDisplay(std::string &results_top, std::string &results_table);

    /**
     * @brief candidate index of the winning candidate
     */
    int idx_win;
    
    /**
     * @brief boolean tracking whether a tie break has occurred
     */
    bool tie_used;
};

#endif