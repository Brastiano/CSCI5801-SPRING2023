/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Andrew Brevick
 * File name: ballot.h
 * Description: Ballot class for storing the vote information within one ballot
 * @endcond
 */

#ifndef BALLOT_H
#define BALLOT_H

#include<iostream>
#include<string>

/**
 * @brief Ballot class used to store vote information
 * 
 */
class Ballot 
{
public:
    /**
     * Create a new Ballot object
     * @brief Default constructor
     * @see Ballot(std::string line, int id)
     * This default constructor is only used to instantiate temporary Ballot pointers
     */
    Ballot();

    /**
     * @brief Construct a new Ballot object
     * @see Ballot()
     * @param line full string of ballot information from the input file
     * @param id index of this ballot in the ballot file
     */
    Ballot(std::string line, int id);

    /**
     * @brief Ballot destructor
     * 
     */
    ~Ballot();

    /**
     * @brief Get the candidate index of the candidate to whom this ballot currently belongs
     * 
     * @return int candidate "global" index
     */
    int GetCurrentVote();

    /**
     * @brief increment the vote index within this ballot to the next candidate
     * 
     * @return int new active candidate index
     * @return -1 if no candidates remain
     * 
     * There is no guarantee that the returned candidate is still valid
     * This needs to be checked at the candidate level
     */
    int Increment();

    /**
     * @brief Gets the ballot id which identifies this ballot from the original input file
     * 
     * @return int ballot id
     */
    int GetID();
private:
    /**
     * current active index of vote array (from 0)
     */
    int idx_vote; 
    /**
     * # of candidates voted for on this ballot
     * 
     */
    int n_cand; 
    /**
     * array of votes (stored as candidate indicies), ordered by preference 
     */
    int* votes;  
    /**
     * unique ballot # from input file
     */
    int ballot_id;

// Things related to this being a Node
public:
    /**
     * @brief Get the next Ballot object in linked list
     * 
     * @return Ballot* next entry in linked list
     */
    Ballot* GetNext();

    /**
     * @brief Set the next Ballot object in linked list
     * 
     * @param ballot pointer to Ballot object to be appended on LL
     */
    void SetNext(Ballot* ballot);

    /**
     * @brief pointer to next Ballot in linked list
     */
    Ballot* next;

    /**
     * @brief Count how many candidates are ranked on the current ballot
     * 
     * @param line from ballot input file
     * @return int number of candidates ranked
     */
    int CountVotes(std::string line);
};

#endif