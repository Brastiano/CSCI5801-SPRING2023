/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Cuong Ha
 * File name: cpl.cc
 * Description: This file contains a class called CPL which is one of the two voting methods
 *              to be used in this election. The code basically goes through the steps from
 *              extracting ballots information from an input file, performing necessary
 *              calculations to determine how many seats are assigned to each party, which
 *              participates in the election, in a whole number round and a remainder round.
 *              An audit file, which is already opened from beginning, will be updated on
 *              the way while the calculations are being perform to avoid any interruptions
 *              in program execution. At the end of the process, a result page will be shown
 *              with less information than the audit file itself, yet enough information for
 *              the user to understand how everything
 * @endcond
 */

#include "cpl.h"
#include "party.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cmath>

CPL::CPL(int total_parties, std::string parties, std::string candidates, int total_seats, int total_ballots) {
    this->parties_ptr = new Party(total_parties);
    this->total_parties = total_parties;
    this->parties = parties;
    this->candidates = candidates;
    this->total_seats = total_seats;
    this->initial_seats = total_seats;
    this->total_ballots = total_ballots;
    this->ballots.reserve(total_parties);
    for (int i = 0; i < total_ballots; i++) {
        this->ballots.push_back(0);
    }
    this->quota = float(this->total_ballots) / float(this->total_seats);
}

void CPL::UpdateBallots() {
    std::string line;
    /**
     * Line 1                           : Election type
     * Line 2                           : Number of parties
     * Line 3                           : Parties
     * Line 4 - # parties               : Candidates
     * Line # parties + 1 - End of file : Ballots
     */    
    int header_lines = 5 + this->total_parties;

    // Skip the first couple header lines until reaching the ballots
    for (int i = 0; i < header_lines; i++)
        std::getline(Election::input_file, line);
    
     // For counting the vote
    std::string output = "Counting process: \n";
    
    // Read the ballots
    for (int i = 0; i < this->total_ballots; i++) {
        std::getline(Election::input_file, line);
        // ballots += line;
        // ballots += "\n";
        std::size_t index = line.find("1");
        this->ballots.at(index) += 1;
        output += "Party ";
        output += std::to_string(index + 1);
        output += ": +1 vote\n";
    }
    
    output += "-------------------------------------------------------------------------------------------------------------------------\n";
    Election::WriteAuditFile(output);
}

void CPL::InitializeParty() {
    /**
     * Party's constructor needs:
     *    1. std::vector<std::string> parties_names
     *    2. std::vector<std::vector<std::string>> candidates_names
     *    4. std::vector<int> available_candidates
     *    5. std::vector<int> votes_amounts
     *    6. std::vector<int> assigned_seats
     */

    // Convert string of parties names into a vector of strings
    std::vector<std::string> p_names = this->ToVectorString();
    this->parties_ptr->SetPartiesNames(p_names);

    // Convert string of candidates names into a vector of vector of strings
    std::vector<std::vector<std::string>> c_names = this->ToVectorVectorString();
    this->parties_ptr->SetCandidatesNames(c_names);

    // Calculate the number of available candidates
    std::vector<int> candidates_per_party;
    candidates_per_party.reserve(this->total_parties);
    for (int i = 0; i < c_names.size(); i++) {
        candidates_per_party.push_back(c_names.at(i).size());
    }
    this->parties_ptr->SetAvailableCandidates(candidates_per_party);
    
    // Convert the string of ballots into vector of ballots
    // std::vector<int> v_amounts = this->ToVectorInt();
    // this->parties_ptr->SetVotesAmounts(v_amounts);
    this->parties_ptr->SetVotesAmounts(this->ballots);

    // Initialize the initial number of seats each party has
    std::vector<int> a_seats;
    a_seats.reserve(this->total_parties);
    for (int i = 0; i < this->total_parties; i++)
        a_seats.push_back(0);
    this->parties_ptr->SetAssignedSeats(a_seats);
}

void CPL::ProcessElection(std::string& top_section, std::string& bottom_section) {
    // Write intitial information into audit file
    this->WriteToAudit(0);

    // Take in the ballots information
    this->UpdateBallots();

    // Set up the necessary variables for Party
    this->InitializeParty();
    
    // Whole number round
    this->ProcessWholeNumberRound();

    // Store number of seats of the parties after first round
    this->parties_ptr->StoreFirstRoundSeats();

    // Write the result to audit file after finishing whole number round
    this->WriteToAudit(1);
    
    // Sort the parties based on their remaining votes count
    this->SortParties();
    
    // Remainder round
    this->ProcessRemainderRound();
    
    // Write the final results to audit file after finishing remainder round
    this->WriteToAudit(2);

    // Write the results to the last page of the GUI
    this->WriteDisplayPage(top_section, bottom_section);
}

void CPL::ProcessWholeNumberRound() {
    for (int i = 0; i < this->total_parties; i++) {
        // Calculate the number of seats this party is going to get
        int seats_amount = this->parties_ptr->GetVotesAmount(i) / this->quota;        
        // Call the function to start assigning seats
        this->AssignSeatsWholeNumber(i, seats_amount);
    }
}

void CPL::ProcessRemainderRound() {
    for (int i = 0; i < this->total_parties; i++) {
        // Extract the number of remaining votes this party has
        int counts = this->parties_ptr->GetVotesAmount(i);

        // Look for the parties that have the same number of votes, starting at index i
        std::vector<int> same_votes_parties = this->FindTiedParties(i, counts);
        for (int i=0;i<same_votes_parties.size();i++)

        // Breaking tie if there are not enough seats for every party
        if (this->total_seats < same_votes_parties.size()) {
            i += (same_votes_parties.size() - 1);
            while (this->total_seats > 0) {
                int lucky_id = Election::FlipCoin(same_votes_parties.size());
                this->AssignSeatsRemainder(same_votes_parties.at(lucky_id));
                this->coin_flipped_remainder_round = true;
                // Remove the chosen party from the list to avoid multiple seats assignments
                same_votes_parties.erase(same_votes_parties.begin() + lucky_id);         
                if (same_votes_parties.size() == 0) break;
            }
            if (this->total_seats <= 0) break;
        } else if (this->total_seats >= same_votes_parties.size()) {
            for (int j = 0; j < same_votes_parties.size(); j++)
                this->AssignSeatsRemainder(same_votes_parties.at(j));
            i += (same_votes_parties.size() - 1);
        }
        
        // If after having gone through all parties and there are still seats left, return to the first one
        if (this->total_seats > 0 && i == (this->total_parties - 1))
            i = -1;
    }
}

Party* CPL::GetParties() const {
    return this->parties_ptr;
}

int CPL::GetTotalParties() const {
    return this->total_parties;
}

int CPL::GetTotalSeats() const {
    return this->total_seats;
}

int CPL::GetTotalBallots() const {
    return this->total_ballots;
}

float CPL::GetQuota() const {
    return this->quota;
}

void CPL::AssignSeatsWholeNumber(int party_index, int seats_amount) {
    /*
     * If the party cannot receive any more seats, returns 0.
     * If the party can receive all seats, returns 1.
     * If the party can receive some seats, returns 2.
     */
    while (seats_amount > 0) {
        int receivable = this->CheckAssignable(party_index, seats_amount);
        if (receivable == 1) {
            this->parties_ptr->ModifySeats(party_index, seats_amount);
            int num_avail = this->parties_ptr->GetAvailableCandidates(party_index);
            this->parties_ptr->ModifyAvailableCandidates(party_index, -seats_amount);
            int deducted_amount = floor(this->quota) * seats_amount;
            this->parties_ptr->ModifyVotes(party_index, -deducted_amount);
            this->total_seats -= seats_amount;
            break;
        } else if (receivable == 2) {            
            int num_avail = this->parties_ptr->GetAvailableCandidates(party_index);
            this->parties_ptr->ModifySeats(party_index, num_avail);
            this->parties_ptr->ModifyAvailableCandidates(party_index, -num_avail);
            int deducted_amount = floor(this->quota) * num_avail;
            this->parties_ptr->ModifyVotes(party_index, -deducted_amount);
            seats_amount -= num_avail;
            this->total_seats -= num_avail;
        }
        party_index = Election::FlipCoin(this->total_parties);
        this->coin_flipped_whole_number_round = true;
    }
}

void CPL::AssignSeatsRemainder(int party_index) {
    int receivable = this->CheckAssignable(party_index, 1);
    if (receivable == 1) {
        // Assign seats to this party
        this->parties_ptr->ModifySeats(party_index, 1);

        // Decrement the number of available candidates this party has
        this->parties_ptr->ModifyAvailableCandidates(party_index, -1);

        // Record how many additional seats are added to this party in this round
        this->parties_ptr->ModifyChangeInSeats(party_index, 1);
        
        // Decrement total number of seats by 1
        this->total_seats--;
    }
}

int CPL::CheckAssignable(int party_index, int seats_amount) {
    /*
     * If the party cannot receive any more seats, returns 0.
     * If the party can receive all seats, returns 1.
     * If the party can receive some seats, returns 2.
     */
    int num_avail = this->parties_ptr->GetAvailableCandidates(party_index);
    if (num_avail == 0) return 0;
    else if (num_avail >= seats_amount) return 1;
    else return 2;
}

void CPL::SortParties() {
    // Use selection sort
    for (int i = 0; i < this->total_parties - 1; i++) {
        int largest = i;
        for (int j = i + 1; j < this->total_parties; j++) {
            int num_votes_largest = this->parties_ptr->GetVotesAmount(largest);
            int num_votes = this->parties_ptr->GetVotesAmount(j);
            if (num_votes > num_votes_largest)
                largest = j; 
        }        
        this->parties_ptr->SwapParties(largest, i);
    }
}

std::vector<int> CPL::FindTiedParties(int index, int amount) {
    std::vector<int> tied_parties;
    
    // Find all the parties that have the same number of votes
    for (int i = index; i < this->total_parties; i++) {
        int counts = this->parties_ptr->GetVotesAmount(i);
        if (counts == amount)
            tied_parties.push_back(i);
    }

    return tied_parties;
}

void CPL::WriteDisplayPage(std::string& top, std::string& bottom) {
    // Use this to manipulate the stream for aligning information
    std::stringstream stream_top;
    std::stringstream stream_bottom;

    // Top section
    stream_top << "Number of attended parties: " << std::to_string(this->total_parties) << std::endl;
    stream_top << "Number of ballots received: " << std::to_string(this->total_ballots) << std::endl;
    stream_top << "Number of seats: " << std::to_string(this->initial_seats) << std::endl;
    int num_candidates = 0;
    for (int i = 0; i < this->total_parties; i++)
        num_candidates += this->parties_ptr->GetCandidatesCount(i);
    stream_top << "Number of candidates: " << std::to_string(num_candidates) << std::endl;
    stream_top << "********************************" << std::endl;
    top = stream_top.str();

    // Bottom section
    stream_bottom << std::left << std::setw(30) << "Party";
    for (int i = 0; i < this->total_parties; i++)
        stream_bottom << std::left << std::setw(20) << this->parties_ptr->GetPartyName(i);
    stream_bottom << std::endl;

    stream_bottom << std::left << std::setw(30) << "Number of candidates: ";
    for (int i = 0; i < this->total_parties; i++)
        stream_bottom << std::left << std::setw(20) << this->parties_ptr->GetCandidatesCount(i);
    stream_bottom << std::endl;

    stream_bottom << std::left << std::setw(30) << "Initial votes amount: ";
    for (int i = 0; i < this->total_parties; i++)
        stream_bottom << std::left << std::setw(20) << this->parties_ptr->GetInitialVotesAmount(i);
    stream_bottom << std::endl;

    stream_bottom << std::left << std::setw(30) << "First seats allocation: ";
    for (int i = 0; i < this->total_parties; i++)
        stream_bottom << std::left << std::setw(20) << this->parties_ptr->GetFirstRoundSeats(i);
    stream_bottom << std::endl;

    stream_bottom << std::left << std::setw(30) << "Remaining votes amount: ";
    for (int i = 0; i < this->total_parties; i++)
        stream_bottom << std::left << std::setw(20) << this->parties_ptr->GetVotesAmount(i);
    stream_bottom << std::endl;

    stream_bottom << std::left << std::setw(30) << "Final seats allocation: ";
    for (int i = 0; i < this->total_parties; i++)
        stream_bottom << std::left << std::setw(20) << this->parties_ptr->GetAssignedSeats(i);
    stream_bottom << std::endl;

    stream_bottom << std::left << std::setw(30) << "Percentage of votes: ";
    for (int i = 0; i < this->total_parties; i++)
        stream_bottom << std::left << std::setw(20) << std::to_string(this->parties_ptr->GetInitialVotesAmount(i) * 100 / this->total_ballots);
    stream_bottom << std::endl;

    stream_bottom << std::left << std::setw(30) << "Percentage of seats: ";
    for (int i = 0; i < this->total_parties; i++)
        stream_bottom << std::left << std::setw(20) << std::to_string(this->parties_ptr->GetAssignedSeats(i) * 100 / this->initial_seats);
    stream_bottom << std::endl;

    bottom = stream_bottom.str();
}

std::vector<std::string> CPL::ToVectorString() {
    std::vector<std::string> p_vector;
    p_vector.reserve(this->total_parties);

    std::stringstream ss(this->parties);
    std::string party;
    while (std::getline(ss, party, ',')) {
        if (party[0] == ' ')
            party = party.substr(1, party.size() - 1);
        p_vector.push_back(party);
    }

    return p_vector;
}

std::vector<std::vector<std::string>> CPL::ToVectorVectorString() {
    std::vector<std::vector<std::string>> c_vectors;
    c_vectors.reserve(this->total_parties);

    // This string variable will be used for both step 1 and 2
    std::string candidates_each_party;

    // Step 1: Break candidates into different parties
    std::vector<std::string> temp;
    temp.reserve(this->total_parties);
    std::stringstream ss_temp(candidates);
    while (std::getline(ss_temp, candidates_each_party, '\n'))
        temp.push_back(candidates_each_party);

    // Step 2: Break candidates of each party into different strings
    for (int i = 0; i < temp.size(); i++) {
        candidates_each_party = temp.at(i);
        std::vector<std::string> temp_2;
        std::string candidate;
        std::stringstream ss_temp_2(candidates_each_party);
        while (std::getline(ss_temp_2, candidate, ','))
            temp_2.push_back(candidate);
        c_vectors.push_back(temp_2);
    }

    return c_vectors;
}

void CPL::WriteToAudit(int round) {
    if (round == 0) this->WriteHeaderToAudit();
    else if (round == 1) this->WriteWholeRoundToAudit();
    else if (round == 2) this->WriteRemainderRoundToAudit();
}

void CPL::WriteHeaderToAudit() {
    std::string output = "**********START*OF*AUDIT*FILE**********\n\n";
    output += "Election type: CPL\n";
    output += "Number of parties: ";
    output += std::to_string(this->total_parties);
    output += "\n";
    output += "Total number of ballots: ";
    output += std::to_string(this->total_ballots);
    output += "\n";
    output += "Total number of seats: ";
    output += std::to_string(this->initial_seats);
    output += "\n-------------------------------------------------------------------------------------------------------------------------\n";
    Election::WriteAuditFile(output);
}

void CPL::WriteWholeRoundToAudit() {
    // Use this to manipulate the stream for aligning information
    std::stringstream stream;

    stream << "Round 1: Whole number seats assignment" << std::endl;

    stream << "---------Quota value: " << std::to_string(this->quota) << std::endl;

    stream << std::left << std::setw(30) << "Party";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetPartyName(i);
    stream << std::endl;

    stream << std::left << std::setw(30) << "Number of candidates";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetCandidatesCount(i);
    stream << std::endl;

    stream << std::left << std::setw(30) << "Votes received";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetInitialVotesAmount(i);
    stream << std::endl;

    stream << std::left << std::setw(30) << "Votes/quota ratio";
    for (int i = 0; i < this->total_parties; i++) {
        float ratio = floor(this->parties_ptr->GetInitialVotesAmount(i) / float(this->quota));
        stream << std::left << std::setw(20) << std::to_string(round(ratio * 100.0) / 100.0);
    }        
    stream << std::endl;

    stream << std::left << std::setw(30) << "First seats allocation";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetFirstRoundSeats(i);
    stream << std::endl;

    stream << std::left << std::setw(30) << "Remaining candidates";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetAvailableCandidates(i);
    stream << std::endl;

    stream << std::left << std::setw(30) << "Votes deducted";
    for (int i = 0; i < this->total_parties; i++) {
        int deducted_amount = this->parties_ptr->GetFirstRoundSeats(i) * int(this->quota);
        stream << std::left << std::setw(20) << std::to_string(deducted_amount);
    }        
    stream << std::endl;

    stream << std::left << std::setw(30) << "Remaining votes";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetVotesAmount(i);
    stream << std::endl;

    stream << "---------Remaining seats: " << this->total_seats << std::endl;

    if (this->coin_flipped_whole_number_round == true) stream << "---------Coin flipped this round: Yes" << std::endl;
    else stream << "---------Coin flipped this round: No" << std::endl;

    stream << "-------------------------------------------------------------------------------------------------------------------------";

    std::string output = stream.str();

    Election::WriteAuditFile(output);
}

void CPL::WriteRemainderRoundToAudit() {
    // Use this to manipulate the stream for aligning information
    std::stringstream stream;
    
    stream << std::endl << "Round 2: Remainder seats assignment (Parties are now ranked by remaining votes)" << std::endl;

    stream << std::left << std::setw(30) << "Party";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetPartyName(i);
    stream << std::endl;

    stream << std::left << std::setw(30) << "Remaining votes";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetVotesAmount(i);
    stream << std::endl;

    stream << std::left << std::setw(30) << "First seats allocation";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetFirstRoundSeats(i);
    stream << std::endl;

    stream << std::left << std::setw(30) << "Change in seats";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetChangeInSeats(i);
    stream << std::endl;

    stream << std::left << std::setw(30) << "Final seats allocation";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetAssignedSeats(i);
    stream << std::endl;

    stream << std::left << std::setw(30) << "Remaining candidates";
    for (int i = 0; i < this->total_parties; i++)
        stream << std::left << std::setw(20) << this->parties_ptr->GetAvailableCandidates(i);
    stream << std::endl;
    
    if (this->coin_flipped_remainder_round == true) stream << "---------Coin flipped this round: Yes" << std::endl;
    else stream << "---------Coin flipped this round: No" << std::endl;

    stream << std::endl << std::endl << "***********END*OF*AUDIT*FILE***********";

    std::string output = stream.str();

    Election::WriteAuditFile(output);
}