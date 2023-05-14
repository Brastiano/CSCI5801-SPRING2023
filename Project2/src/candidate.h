/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Andrew Brevick
 * File name: candidate.h
 * Description: Candidate class which stores ballots
 * @endcond
 */

#ifndef CANDIDATE_H
#define CANDIDATE_H

#include"ballot.h"
#include<iostream>
#include<string>

/**
 * @brief Candidate class. Primary function is to store a linked list of Ballots
 * 
 */
class Candidate
{
public: 
    /**
     * @brief Construct a new Candidate object
     * 
     * @param nm name of candidate
     * @param prt party of candidate
     * @see Candidate()
     */
    Candidate(std::string nm, std::string prt); 

    /**
     * @brief Construct a new Candidate object
     * @see Candidate(std::string nm, std::string prt)
     */
    Candidate();

    /**
     * @brief Initialize a candidate that was instantiated with the default constructor
     * Candidates are created in arrays, so the default constructor is often used
     * @param nm name of candidate
     * @param prt party of candidate
     */
    void Init(std::string nm, std::string prt);

    /**
     * @brief Add a Ballot object to this candidate's linked list
     * 
     * @param ballot Ballot object to append
     */
    void AssignBallot(Ballot* ballot);

    /**
     * @brief Remove a Ballot object from this candidate's linked list
     * 
     * @return Ballot* Ballot pointer so that the Ballot can be reassigned
     */
    Ballot* RemoveBallot();

    /**
     * @brief Get the current number of votes belonging to this candidate
     * 
     * @return int vote count
     */
    int GetVoteCount();

    /**
     * @brief Get the number of votes belonging to this candidate at the end of the previous round
     * 
     * @return int previous vote count
     */
    int GetPrevVoteCount();

    /**
     * @brief Update the current number of votes belonging to this candidate
     * 
     */
    void SetPrevVoteCount();

    /**
     * @brief candidate name
     * 
     */
    std::string name;

    /**
     * @brief candidate party
     * 
     */
    std::string party;

    /**
     * @brief Get a comma separated string of all ballots belonging to this candidate
     * 
     * @return std::string 
     */
    std::string GetVoteIDs();
private:
    
    /**
     * @brief current count of votes
     * 
     */
    int n_votes;

    /**
     * @brief count of votes for this candidate during the previous round
     * 
     */
    int n_votes_prev_round;

    /**
     * @brief pointer to first ballot in linked list
     * 
     */
    Ballot* first_ballot;

    /**
     * @brief pointer to last ballot in linked list
     * 
     */
    Ballot* last_ballot;
};

#endif