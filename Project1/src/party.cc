/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Cuong Ha
 * File name: party.cc
 * Description: This file contains a class called Party which is a class that represents
 *              the information of all parties that participated in the election. The
 *              information is then extracted by class CPL to determine how many seats are
 *              assigned to each party after a whole number round and a remainder round.
 * @endcond
 */

#include "party.h"
#include <vector>
#include <iostream>

Party::Party(int num_parties) {
    this->parties_names.reserve(num_parties);
    this->candidates_names.reserve(num_parties);
    this->candidates_per_party.reserve(num_parties);
    this->available_candidates.reserve(num_parties);
    this->votes_amounts.reserve(num_parties);
    this->initial_votes_amounts.reserve(num_parties);
    this->assigned_seats.reserve(num_parties);
    this->first_round_assigned_seats.reserve(num_parties);
    this->change_in_seats.reserve(num_parties);
    for (int i = 0; i < num_parties; i++)
        this->change_in_seats.push_back(0);
}

void Party::SetPartiesNames(std::vector<std::string> names) {
    this->parties_names = names;
}

void Party::SetCandidatesNames(std::vector<std::vector<std::string>> names) {
    this->candidates_names = names;
}

void Party::SetAvailableCandidates(std::vector<int> available_candidates) {
    this->available_candidates = available_candidates;
    this->candidates_per_party = available_candidates;
}

void Party::SetVotesAmounts(std::vector<int> votes_amounts) {
    this->votes_amounts = votes_amounts;
    this->initial_votes_amounts = votes_amounts;
}

void Party::SetAssignedSeats(std::vector<int> assigned_seats) {
    this->assigned_seats = assigned_seats;
}

std::string Party::GetPartyName(int party_index) const {
    return this->parties_names.at(party_index);
}

std::string Party::GetCandidateName(int party_index, int candidate_index) const {
    return this->candidates_names.at(party_index).at(candidate_index);
}

int Party::GetCandidatesCount(int party_index) {
    return this->candidates_per_party.at(party_index);
}

int Party::GetAvailableCandidates(int party_index) const {
    return this->available_candidates.at(party_index);
}

int Party::GetVotesAmount(int party_index) const {
    return this->votes_amounts.at(party_index);
}

int Party::GetFirstRoundSeats(int party_index) const {
    return this->first_round_assigned_seats.at(party_index);
}

int Party::GetInitialVotesAmount(int party_index) const {
    return this->initial_votes_amounts.at(party_index);
}

int Party::GetAssignedSeats(int party_index) const {
    return this->assigned_seats.at(party_index);
}

int Party::GetChangeInSeats(int party_index) const {
    return this->change_in_seats.at(party_index);
}

void Party::ModifyVotes(int party_index, int amount) {
    this->votes_amounts.at(party_index) += amount;
}

void Party::ModifySeats(int party_index, int amount) {
    this->assigned_seats.at(party_index) += amount;
}

void Party::ModifyChangeInSeats(int party_index, int amount) {
    this->change_in_seats.at(party_index) += amount;
}

void Party::ModifyAvailableCandidates(int party_index, int amount) {
    if (-amount >= this->available_candidates.at(party_index)) {
        this->available_candidates.at(party_index) = 0;
        return;
    }
    this->available_candidates.at(party_index) += amount;
}

void Party::SwapParties(int first_index, int second_index) {
    int integer_temp;
    std::string str_temp;
    std::vector<int> integer_vector_temp;
    std::vector<std::string> str_vector_temp;
    
    // Swap parties_names
    str_temp = this->parties_names.at(first_index);
    this->parties_names.at(first_index) = this->parties_names.at(second_index);
    this->parties_names.at(second_index) = str_temp;

    // Swap candidates_names
    str_vector_temp = this->candidates_names.at(first_index);
    this->candidates_names.at(first_index) = this->candidates_names.at(second_index);
    this->candidates_names.at(second_index) = str_vector_temp;

    // Swap candidates_per_party
    integer_temp = this->candidates_per_party.at(first_index);
    this->candidates_per_party.at(first_index) = this->candidates_per_party.at(second_index);
    this->candidates_per_party.at(second_index) = integer_temp;

    // Swap available_candidates
    integer_temp = this->available_candidates.at(first_index);
    this->available_candidates.at(first_index) = this->available_candidates.at(second_index);
    this->available_candidates.at(second_index) = integer_temp;

    // Swap votes_amounts
    integer_temp = this->votes_amounts.at(first_index);
    this->votes_amounts.at(first_index) = this->votes_amounts.at(second_index);
    this->votes_amounts.at(second_index) = integer_temp;

    // Swap initial_votes_amounts
    integer_temp = this->initial_votes_amounts.at(first_index);
    this->initial_votes_amounts.at(first_index) = this->initial_votes_amounts.at(second_index);
    this->initial_votes_amounts.at(second_index) = integer_temp;

    // Swap assigned_seats
    integer_temp = this->assigned_seats.at(first_index);
    this->assigned_seats.at(first_index) = this->assigned_seats.at(second_index);
    this->assigned_seats.at(second_index) = integer_temp;

    // Swap first_round_assigned_seats
    integer_temp = this->first_round_assigned_seats.at(first_index);
    this->first_round_assigned_seats.at(first_index) = this->first_round_assigned_seats.at(second_index);
    this->first_round_assigned_seats.at(second_index) = integer_temp;

    // Swap change_in_seats
    integer_temp = this->change_in_seats.at(first_index);
    this->change_in_seats.at(first_index) = this->change_in_seats.at(second_index);
    this->change_in_seats.at(second_index) = integer_temp;
}

void Party::StoreFirstRoundSeats() {
    this->first_round_assigned_seats = this->assigned_seats;
}