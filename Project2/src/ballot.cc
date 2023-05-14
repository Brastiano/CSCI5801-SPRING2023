/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Andrew Brevick
 * File name: ballot.cc
 * Description: Ballot class for storing the vote information within one ballot
 * @endcond
 */

#include"ballot.h"
#include<string>

Ballot::Ballot()
{
    next = nullptr;
    ballot_id = -1;
    n_cand = -1;
    votes = &n_cand;
}

Ballot::Ballot(std::string line, int id)
{
    next = nullptr;
    ballot_id = id;

    // Parse line to get n_cand and the actual candidates
    // Traverse once to get total number of candidates
    n_cand = CountVotes(line);
    votes = new int[n_cand];

    // Traverse a second time and put the candidate indices 
    // into the array at the appropriate vote positions
    int comma;
    int idx_vote_in;
    int idx_cand = 0;
    while(true) // will continue as long as there are commas in line
    {
        // find the next comma or end line
        comma = line.find(",");
        if (comma == std::string::npos) 
        {
            // check if theres a vote in the last position
            if (line.size()>0) 
            {
                idx_vote_in = std::stoi(line) - 1; // ranking value at which to store the current candidate
                votes[idx_vote_in] = idx_cand;
            }
            break;
        }
        else if (comma != 0 )
        {
            // process the element up to the next comma
            idx_vote_in = std::stoi(line.substr(0,comma)) - 1;
            votes[idx_vote_in] = idx_cand;
        }
        // remove the first element from line
        line = line.substr(comma+1);
        idx_cand++;
    }
    idx_vote = 0; // Set initial vote to highest ranked candidate
};

Ballot::~Ballot()
{
    delete votes;
};

int Ballot::CountVotes(std::string line)
{
    // Count how many candidates are ranked on the current ballot
    int count = 0;
    int comma;
    while(true)
    {
        comma = line.find(",");
        if (comma == std::string::npos) // end of line reached
        {
            // check if theres a vote at the last index
            if(line.size() > 0) {count++;}
            break;
        }
        else if (comma == 0) // element is empty - no vote
        {
            line = line.substr(comma+1);
            continue;
        }
        line = line.substr(comma+1);
        count++; // element is not the last and is not empty
    }
    return count;
}

int Ballot::GetID()
{
    // Gets the ballot id which identifies this ballot from the original input file
    return ballot_id;
};

int Ballot::GetCurrentVote()
{
    // Return the global candidate index of the candidate to whom this ballot currently belongs
    return votes[idx_vote];
};
    
    
int Ballot::Increment()
{
    // Move the vote of this ballot to the next candidate
    // Note: This is not the next *eligible* candidate
    // This check must happen at the candidate level
    idx_vote += 1;
    if (idx_vote == n_cand)
    {
        // Ballot has exhasuted all votes
        return -1;
    }
    return GetCurrentVote(); 
};


Ballot* Ballot::GetNext()
{
    return this->next; 
};

void Ballot::SetNext(Ballot* ballot)
{
    next = ballot;
};
