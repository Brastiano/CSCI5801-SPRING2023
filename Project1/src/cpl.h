/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Cuong Ha
 * File name: cpl.h
 * Description: This file contains class definition for class CPL. It provides the structure
 *              for class CPL and provides an abstract visualization of what attributes and
 *              methods will be included and used during the tabulation process.
 * @endcond
 */

#ifndef CPL_H
#define CPL_H

#include "election.h"
#include "party.h"
#include <vector>

class CPL : public Election {
    private:
        Party* parties_ptr;
        std::string parties;
        int total_parties;
        int total_seats;
        int initial_seats;
        int total_ballots;
        std::string candidates;
        // std::string ballots;
        std::vector<int> ballots;
        float quota;
        bool coin_flipped_whole_number_round = false;
        bool coin_flipped_remainder_round = false;
    
    public:
        /**
         * @brief Constructor for CPL class
         * @param total_parties Number of parties taking part in an election
         * @param parties String of names of all parties
         * @param candidates String of names of all candidates
         * @param total_seats Number of seats available to be assigned in this election
         * @param total_ballots Number of ballots received for an entire election
         * @param ballots String of the ballots
         */
        CPL(int total_parties, std::string parties, std::string candidates, int total_seats, int total_ballots);

        /**
         * @brief Destructor of CPL
         */
        ~CPL() {}

        /**
         * @brief Function used to take in the ballots from input file
         */
        void UpdateBallots();

        /**
         * @brief Function used to initialize a Party instance
         */
        void InitializeParty();

        /**
         * @brief Function where the main logic of CPL voting will take place
         * @param top_section A string holding the information related to the election, for tabulation purpose
         * @param bottom_section A string holding the result of the election, for tabulation purpose
         */
        void ProcessElection(std::string& top_section, std::string& bottom_section);

        /**
         * @brief Subfunction of ProcessElection that performs calculations during the whole number round
         */
        void ProcessWholeNumberRound();

        /**
         * @brief Subfunction of ProcessElection that performs calculations during the remainder round
         */
        void ProcessRemainderRound();
        
        /**
         * @brief Function used to extract the pointer to the stored Party instance
         * @return Pointer to the stored Party instance
         */
        Party* GetParties() const;

        /**
         * @brief Function used to extract the number of parties participating in the election
         * @return An integer representing the amount
         */
        int GetTotalParties() const;

        /**
         * @brief Function used to extract the number of seats available to be allocated
         * @return An integer representing the amount
         */
        int GetTotalSeats() const;

        /**
         * @brief Function used to extract the number of ballots received for an entire election
         * @return An integer representing the amount
         */
        int GetTotalBallots() const;

        /**
         * @brief Function used to extract the quota value
         * @return A float representing the result from dividing total_ballots by total_seats
         */
        float GetQuota() const;

        /**
         * @brief Function used to assign seats to a desired party
         * @param party_index Index of the party who is going to receive the seats
         * @param seats_amount The number of seats to be assigned to the party
         * @param remainder_round A way to determine where this function is called
         */
        void AssignSeats(int party_index, int seats_amount, bool remainder_round);

        /**
         * @brief Function used to assign seats to parties in the whole number round
         * @param party_index Index of the party to be given seats
         * @param seats_amount Number of seats to be given
         */
        void AssignSeatsWholeNumber(int party_index, int seats_amount);

        /**
         * @brief Function used to assign seats to parties in the remainder round
         * @param party_index Index of the party to be given seats
         */
        void AssignSeatsRemainder(int party_index);

        /**
         * @brief Fucntion used to check whether a party can still receive more seats
         * @param party_index Index of the party that is going to receive the seats
         * @param seats_amount The number of seats to be assigned to the party
         * @retval 0 if the party cannot receive any more seats
         * @retval 1 if the party can receive all seats
         * @retval 2 if the party can receive some seats
         */
        int CheckAssignable(int party_index, int seats_amount);
        
        /**
         * @brief Function used to sort the parties based on their remaining votes count
         */
         void SortParties();

        /**
         * @brief Function used to find all the parties that have the same votes count
         * @param index An index defining where the search should start
         * @param amount An integer representing the number of votes
         * @return A vector containing all the parties that have the same desired votes count
         */
        std::vector<int> FindTiedParties(int index, int amount);

        /**
         * @brief Function used to modify the strings passed in the ProcessElection function
         * @param top A string holding the information related to the election
         * @param bottom A string holding the result of the election
         */
        void WriteDisplayPage(std::string& top, std::string& bottom);

        /**
         * @brief Function used to convert a string to a vector of strings
         */
        std::vector<std::string> ToVectorString();

        /**
         * @brief Function used to convert a string to a vector of vector of strings
         */
        std::vector<std::vector<std::string>> ToVectorVectorString();

        /**
         * @brief Function used to write the election information and results into audit file
         */
        void WriteToAudit(int round);

        /**
         * @brief Function used to write the header of the audit file
         */
        void WriteHeaderToAudit();

        /**
         * @brief Function used to write the results after the first round to audit file
         */
        void WriteWholeRoundToAudit();

        /**
         * @brief Function used to write the final results to audit file
         */
        void WriteRemainderRoundToAudit();
};

#endif