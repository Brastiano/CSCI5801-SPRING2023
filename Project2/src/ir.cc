/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Andrew Brevick
 * File name: ir.cc
 * Description: Specific strategy of Election for processing IR election logic
 * @endcond
 */

#include"ir.h"

#define TEST_VERBOSE 1
#define AUDIT_VERBOSE 0

IR::IR(int n_cand, std::string all_cand, int n_ball)
{
    // Constructor for IR election type
    // takes header information as arguments to dynamically size member variables

    n_candidates = n_cand;
    n_ballots = n_ball;

    // need to create all candidate classes
    candidates = new Candidate[n_cand];
    std::string one_cand, name, party;
    int len_name;

    for (int idx=0; idx<n_cand; idx++)
    {
        // From the string that contains all canidate names and parties
        // Parse one at a time
        // Separate candidate name and party
        // then use to init the candidate object at that index
        one_cand = GetNextCandidateName(all_cand);
        ParseCandidateName(one_cand, name, party); 
        candidates[idx].Init(name, party); 
    }

    // Create null candidate for dead ballots
    null_candidate = new Candidate[1];
    null_candidate->Init("null","null");

    tie_used = false;
    valid_candidates = 0;
    round_number = 1;
}

// Helper function for IR()
std::string IR::GetNextCandidateName(std::string &all_cand)
{
    int comma = all_cand.find(",");
    if (comma == std::string::npos) // This is the last candidate in the line
    {
        return all_cand;
    }
    std::string temp = all_cand.substr(0,comma-1);
    all_cand = all_cand.substr(comma+1);
    return temp;
};

// Helper function for IR()
void IR::ParseCandidateName(std::string one_cand, std::string &name, std::string &party)
{
    int pos_paren; 
    // Parse candidate name based on the location of the open parenthesis
    pos_paren = one_cand.find("("); 
    name = one_cand.substr(0,pos_paren); // Gets string up to paren
    party = one_cand.substr(pos_paren+1, 1); // Gets the character immediately after the paren
};

int IR::ValidCandidates()
{
    // Count valid candidates
    int count = 0;
    for (int idx = 0; idx<n_candidates; idx++)
    {
        if (candidates[idx].GetVoteCount() > 0) {count++;}
    }
    if (TEST_VERBOSE) {std::cout << "Valid Candidates: " << count << "\n";}
    return count;
};

void IR::ProcessElection(std::string &results_top, std::string &results_table)
{
    // Complete all steps involved in getting to the result of an IR election

    WriteHeaderAudit();
	// Read all ballot files into class
    InputBallots();
    if (TEST_VERBOSE) std::cout << "Ballots input successfully\n";

    InitResultsTable();

    // Write initial state after ballot input to audit
    WriteRoundAudit();
    UpdateResultsTable();

	// Begin round loop
    int idx_min;
    while(valid_candidates>2)
    {
        if (TEST_VERBOSE) std::cout << "Valid Candidates Remaining: " << std::to_string(valid_candidates) << "\n";
        // Perform break checks
        if (CheckMajority()>=0)
        {
            // Winner found
            idx_win = CheckMajority();
            WriteResultAudit(win_type_e::majority);
            UpdateResultsTable();
            SetResultsDisplay(results_top, results_table);
        }

        // No break check succeeded, remove a candidate
		idx_min = FindMin();
        if (TEST_VERBOSE) std::cout << "Reallocating idx: " << idx_min << "\n";
        WriteReallocationAudit(idx_min);
		Reallocate(idx_min);

        WriteRoundAudit();
        UpdateResultsTable();
    }

    // If here, then only 2 candidates remain
    if (CheckMajority()>=0)
    {
        // Winner found
        if (TEST_VERBOSE) std::cout << "\nMajority win\n";
        idx_win = CheckMajority();
        WriteResultAudit(win_type_e::majority);
        UpdateResultsTable();
        SetResultsDisplay(results_top, results_table);
    }
    else 
    {
        // No candidate has majority
        if (TEST_VERBOSE) std::cout << "\npopular win\n";
        int idx1, idx2;
        // get the two candidate indexes 
        FindRemainingCandidates(idx1, idx2);
        idx_win = ResolvePopular(idx1, idx2);
        WriteResultAudit(win_type_e::popular);
        UpdateResultsTable();
        SetResultsDisplay(results_top, results_table);
    }
};

void IR::FindRemainingCandidates(int &idx1, int &idx2)
{
    // When only 2 candidates remain, find their indices
    int idx = 0;
    while (true && idx<n_candidates)
    {
        if (candidates[idx].GetVoteCount() > 0)
        {
            idx1 = idx;
            break;
        }
        idx++;
    }
    idx++;
    while (true && idx<n_candidates)
    {
        if (candidates[idx].GetVoteCount() > 0)
        {
            idx2 = idx;
            break;
        }
        idx++;
    }
};

void IR::InputBallots()
{
    // Read ballot file line by line and create the ballot objects
    // also assign to the appropriate candidates
    if (TEST_VERBOSE) std::cout << "Inputing ballots\n";
    std::string header_temp;
    for(int idx = 0; idx<4; idx++) 
    {
        std::getline(input_file, header_temp);
        if (TEST_VERBOSE) std::cout << header_temp << "\n";
    }
    Ballot* temp;
    int ballot_id = 0; 
    int idx_cand;
    if (TEST_VERBOSE) std::cout << "Inputing ballots\n";
    for(std::string line; std::getline(input_file, line); )
    {
        if (TEST_VERBOSE) std::cout << line << "\n";
        //std::cout << "\nballot_id:" << ballot_id << "\n";
        temp = new Ballot(line, ballot_id); 
        //std::cout<< "\nNew ballot created with ID " << temp->ballot_id << "\n";
        idx_cand = temp->GetCurrentVote(); // Get the candidate index for the first ranked vote on this ballot
        if (TEST_VERBOSE) std::cout << "Assigning ballot" << "\n";
        candidates[idx_cand].AssignBallot(temp); // Add the ballot to the candidate

        ballot_id++; 
    }
    valid_candidates = ValidCandidates();
};

int IR::FindMin()
{
    // Find the candidate with the minimum number of votes to eliminate
    // Deal with ties if they occur
    int min_cand = 0;
    int min_count = candidates[0].GetVoteCount();
    int temp;
    for (int idx = 1; idx<n_candidates; idx++)
    {
        temp = candidates[idx].GetVoteCount();
        if ((temp != 0) && (temp == min_count))
        {
            // We have found a tie
            int flip = FlipCoin(2);
            if (flip > 0)
            {
                min_cand = idx; 
            }
            tie_used = true;
        }
        else if ((temp != 0) && (temp < min_count))
        {
            min_cand = idx;
            min_count = temp;
        }
    }
    return min_cand; 
};

int IR::CheckMajority()
{
    // return -1 if no majority is found
    // otherwise, return the candidate index of the candidate who has acheived majority
    int maj = floor(n_ballots/2); 
    for (int idx = 0; idx<n_candidates; idx++)
    {
        if (candidates[idx].GetVoteCount() > maj) {return idx;}
    }
    return -1;
};

int IR::ResolvePopular(int idx1, int idx2)
{
    // This is triggered in the case that there are only 2 candidates left, 
    // but neither has reached a majority. 
    // In this case, we resolve as a popularity vote
    if (candidates[idx1].GetVoteCount() == candidates[idx2].GetVoteCount())
    {
        if (FlipCoin(2) == 0) // Resolve tie with coin flip
        {
            return idx1;
        }
        else {return idx2;}
        tie_used = true;
    }
    else if (candidates[idx1].GetVoteCount() > candidates[idx2].GetVoteCount())
    {
        return idx1;
    }
    else {return idx2;}
};

void IR::Reallocate(int idx_rm)
{
    // Remove the candidate at idx_rm
    // Reassign all of their ballots to the next available canididate
    Ballot* temp_ball = new Ballot();
    int idx_new;
    if (TEST_VERBOSE) std::cout<< "Reallocating " << candidates[idx_rm].GetVoteCount() << " ballots\n";
    while(candidates[idx_rm].GetVoteCount()>0) 
    {
        // Remove the current first_ballot from the eliminated candidate 
        // and return a pointer to the ballot
        temp_ball = candidates[idx_rm].RemoveBallot(); 
        if (TEST_VERBOSE) std::cout << temp_ball->GetID() << ",";
        // Increment the ballot vote until it goes to either a valid canididate or the null_candidate
        while(true)
        {
            idx_new = temp_ball->Increment();
            if (TEST_VERBOSE) std::cout << idx_new << ",";
            if (idx_new == -1)
            {
                //if (TEST_VERBOSE) std::cout << 
                null_candidate->AssignBallot(temp_ball);
                break;
            }
            else if (candidates[idx_new].GetVoteCount() > 0)
            {
                // Move ballot to new canididate
                candidates[idx_new].AssignBallot(temp_ball);
                break;
            }
        }
    }
    if (TEST_VERBOSE) std::cout << "\nRemaining votes (should be 0): " << candidates[idx_rm].GetVoteCount() << "\n";
    valid_candidates--;
};

void IR::WriteRoundAudit()
{
    // Put all of the current round audit information into a string
    // needs to include each candidate, their vote count, and then 
    if(AUDIT_VERBOSE) std::cout << "Audit file status: " << audit_file.is_open() << "\n";
    std::string out = "\n\nRound Status\n";
    out += "Valid Candidates Remaining: ";
    out += std::to_string(valid_candidates);
    out += "\n";
    WriteAuditFile(out);
    if (AUDIT_VERBOSE) std::cout << "AUDIT:" << out << "\n";
    int n_votes;

    for (int idx = 0; idx < n_candidates; idx++)
    {
        n_votes = candidates[idx].GetVoteCount();
        
        out = "";
        out += "\nCandidate: ";
        out += candidates[idx].name;
        out += "\nVotes: ";
        out += std::to_string(n_votes);
        out += "\n";
        out += "Ballots:";
        out += candidates[idx].GetVoteIDs();
        out += "\n";
        WriteAuditFile(out);
        if (AUDIT_VERBOSE) std::cout << "AUDIT:" << out << "\n";
    }
};

void IR::WriteHeaderAudit()
{
    std::string out;
    out = "Election Type: IR\n";
    out += "Num Candidates: ";
    out += std::to_string(n_candidates); 
    out += " \n";
    WriteAuditFile(out);

    out = "Candidates: ";
    for (int idx = 0; idx<n_candidates; idx++)
    {
        out += candidates[idx].name; 
        out += "(";
        out += candidates[idx].party;
        out += "),";
    }
    out += "\n";
    out += "Num Ballots: ";
    out += std::to_string(n_ballots);
    WriteAuditFile(out);
    // TODO : add date, majority threshold, etc
};

void IR::SetResultsDisplay(std::string &results_top, std::string &results_table)
{
    results_top = "Election Type: IR\n";
    results_top += "Number of Seats: 1\n";
    results_top += "Winning Candidate(s): ";
    results_top += candidates[idx_win].name;
    results_top += " (";
    results_top += candidates[idx_win].party;
    results_top += ")\n";
    results_top += "Total Ballots Tabulated: ";
    results_top += std::to_string(n_ballots);

    
    //, Final Votes, Final Vote Percentage\n"; 
    results_table = results_table_ir;
};

void IR::InitResultsTable()
{
    results_table_ir = "Candidates: \t";
    for (int idx = 0; idx < n_candidates; idx++)
    {
        results_table_ir += candidates[idx].name;
        results_table_ir += ",";
    }
    results_table_ir += "\n";
    results_table_ir += "Party: \t\t";
    for (int idx = 0; idx < n_candidates; idx++)
    {
        results_table_ir += candidates[idx].party;
        results_table_ir += ",";
    }
    results_table_ir += "\n";
}

void IR::UpdateResultsTable()
{
    results_table_ir += "\nRound ";
    results_table_ir += std::to_string(round_number);
    round_number += 1;
    results_table_ir += "\n";
    results_table_ir += " Votes: \t";
    for (int idx = 0; idx < n_candidates; idx++)
    {
        results_table_ir += std::to_string(candidates[idx].GetVoteCount());
        results_table_ir += ",";
    }
    results_table_ir += "\n +/-: \t\t";
    int temp;
    for (int idx = 0; idx < n_candidates; idx++)
    {
        temp = candidates[idx].GetVoteCount() - candidates[idx].GetPrevVoteCount();
        if (temp>=0)
        {
            results_table_ir += "+";
        }
        results_table_ir += std::to_string(temp);
        results_table_ir += ",";
        candidates[idx].SetPrevVoteCount();
    }
    results_table_ir += "\n";
    // Add info for the exhausted pile
    results_table_ir += "Exhausted Pile - Votes: ";
    results_table_ir += std::to_string(null_candidate->GetVoteCount());
    results_table_ir += "   Change +/-: ";
    results_table_ir += std::to_string(null_candidate->GetVoteCount() - null_candidate->GetPrevVoteCount());
    null_candidate->SetPrevVoteCount();
    results_table_ir += "\n";
}

void IR::WriteResultAudit(win_type_e win_type)
{
    std::cout << "Here";
    std::string out = "\n\nResults\nWinner Identified: ";
    out += candidates[idx_win].name;
    out += "\nWinner party: ";
    out += candidates[idx_win].party;
    out += "\n";
    out += "Candidate won via: ";
    if (win_type==win_type_e::majority) {out += "Majority";}
    else {out += "Popular Vote";}
    out += "\nTie Used: ";
    if (tie_used) {out += "Yes\n";}
    else {out += "No\n";}
    WriteAuditFile(out);

    out = "\n\nParty, Final Votes, Final Vote Percentage\n";
    for (int idx = 0; idx < n_candidates; idx++)
    {
        out += candidates[idx].name;
        out += ",";
        out += std::to_string(candidates[idx].GetVoteCount());
        out += ",";
        out += std::to_string(100*candidates[idx].GetVoteCount()/n_ballots);
        out += "%\n";
    }
    WriteAuditFile(out);
    audit_file.close();
    return;
};

void IR::WriteReallocationAudit(int idx_min)
{
    std::string out = "\n\nReallocation\n";
    out += "Candidate Reallocated: ";
    out += candidates[idx_min].name;
    out += "\n";
    out += "Tie Used: ";
    if (tie_used) {out += "Yes\n";}
    else {out += "No\n";}
    tie_used = false;
    WriteAuditFile(out);
    return;
};


std::string IR::GetCandidateName(int candidate_index)
{
    return candidates[candidate_index].name;
};
