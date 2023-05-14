/**
 * \cond DOXYGEN SKIPS THIS
 * Contributor(s): Cuong Ha
 * File name: party.h
 * Description: This file contains class definition for class Party. It provides the structure
 *              for class Party and provides an abstract visualization of what attributes and
 *              methods will be included and used by class CPL during the tabulation process.
 * @endcond
 */

#ifndef PARTY_H
#define PARTY_H

#include <vector>
#include <string>

class Party {
    private:
        std::vector<std::string> parties_names;
        std::vector<std::vector<std::string>> candidates_names;
        std::vector<int> candidates_per_party;
        std::vector<int> available_candidates;
        std::vector<int> votes_amounts;
        std::vector<int> initial_votes_amounts;
        std::vector<int> assigned_seats;
        std::vector<int> first_round_assigned_seats;
        std::vector<int> change_in_seats;
    
    public:
        
        /**
         * @brief Constructor of class Party.
         *        We only reserve the space for storages here, and will fill in the values later
         * @param num_parties Number of parties participating in the election
         */
        Party(int num_parties);
        
        /**
         * @brief Destructor of class Party
         */
        ~Party() {}

        /**
         * @brief Function used to store names of all the parties
         * @param names Vector containing names of all the parties read from the input file
         * @example <"Democratic", "Republican", "Independent">
         */
        void SetPartiesNames(std::vector<std::string> names);

        /**
         * @brief Function used to store names of all the candidates each party has
         * @param names Vector containing names of all the candidates read from the input file
         * @example <<"John", "Mary">, <"Scott", "Judy", "Sarah">, <"Brandon">>
         */
        void SetCandidatesNames(std::vector<std::vector<std::string>> names);

        /**
         * @brief Function used to store the number of available candidates each party has.
         *        This also stores the number of candidates each party has
         * @param names Vector containing all candidate availabilities inferred from the input file
         * @example <2, 3, 1>
         */
        void SetAvailableCandidates(std::vector<int> available_candidates);

        /**
         * @brief Function used to store the number of votes each party has
         * @param votes_amounts Vector containing all the vote counts each party has
         * @example <5, 7, 3>
         */
        void SetVotesAmounts(std::vector<int> votes_amounts);

        /**
         * @brief Function used to store the number of seats already assigned to each party
         * @param assigned_seats Vector containing all the seat counts each party has
         * @example At the start of an election, this should be <0, 0, 0>
         */
        void SetAssignedSeats(std::vector<int> assigned_seats);

        /**
         * @brief Function used to extract the name of a party at some desired index
         * @param party_index Index of the party whose name is wanted
         * @return A string representing the name of the party
         */
        std::string GetPartyName(int party_index) const;

        /**
         * @brief Function used to extract the name of a candidate in some desired party
         * @param party_index Index of the party whose candidate' name is wanted
         * @param candidate_index Index of the candidate in the party whose name is wanted
         * @return A string representing the name of the candidate
         */
        std::string GetCandidateName(int party_index, int candidate_index) const;

        /**
         * @brief Function used to extract the number of candidates the desired party has
         * @param party_index Index of the party whose candidate count is wanted
         * @return An integer representing the number of candidates
         */
        int GetCandidatesCount(int party_index);

        /**
         * @brief Function used to extract the number of available candidates the desired party has
         * @param party_index Index of the party whose candidate availability is wanted
         * @return An integer representing the number of available candidates
         */
        int GetAvailableCandidates(int party_index) const;

        /**
         * @brief Function used to extract the number of votes the desired party receives
         * @param party_index Index of the party whose votes count is wanted
         * @return An integer representing the number of votes
         */
        int GetVotesAmount(int party_index) const;

        /**
         * @brief Function used to extract the number of seats the desired party receives after first round
         * @param party_index Index of the party whose seats count is wanted
         * @return An integer representing the number of assigned seats
         */
        int GetFirstRoundSeats(int party_index) const;

        /**
         * @brief Function used to extract the initial votes the party receives
         * @param party_index Index of the party whose initial votes count is wanted
         * @return An integer representing the number of votes
         */
        int GetInitialVotesAmount(int party_index) const;

        /**
         * @brief Function used to extract the number of seats already assigned to the desired party
         * @param party_index Index of the party whose seats count is wanted
         * @return An integer representing the number of seats
         */
        int GetAssignedSeats(int party_index) const;

        /**
         * @brief Function used to record the change in seats of a party from whole number to remainder round
         * @param party_index Index of the party
         */
        int GetChangeInSeats(int party_index) const;

        /**
         * @brief Function used to modify the votes amount of a party
         * @param party_index Index of the party to be modified
         * @param amount The number of votes to be taken out
         */
        void ModifyVotes(int party_index, int amount);

        /**
         * @brief Function used to modify the seats amount of a party
         * @param party_index Index of the party to be modified
         * @param amount The number of seats to be added
         */
        void ModifySeats(int party_index, int amount);

        /**
         * @brief Function used to modify how many additional seats are assigned to a party
         * @param party_index Index of the party
         * @param amount The number of additional seats
         */
        void ModifyChangeInSeats(int party_index, int amount);

        /**
         * @brief Function used to modify the number of available candidates of a party
         * @param party_index Index of the party to be modified
         * @param amount The number of candidates to be taken out
         */
        void ModifyAvailableCandidates(int party_index, int amount);

        /**
         * @brief Function used to swap the positions of two parties and their related information
         * @param first_index Index of the first party
         * @param second_index Index of the second party
         */        
        void SwapParties(int first_index, int second_index);

        /**
         * @brief Function used to store the information of parties after first round
         */
        void StoreFirstRoundSeats();
};


#endif