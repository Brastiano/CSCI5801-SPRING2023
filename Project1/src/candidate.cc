/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Andrew Brevick
 * File name: candidate.cc
 * Description: Candidate class which stores ballots
 * @endcond
 */

#include"candidate.h"

Candidate::Candidate(std::string nm, std::string prt)
{
    name            = nm;
    party           = prt;
    n_votes         = 0;
    first_ballot    = nullptr;
    last_ballot     = nullptr;
};

Candidate::Candidate()
{
    name            = "";
    party           = "";
    n_votes         = 0;
    first_ballot    = nullptr;
    last_ballot     = nullptr;
}

void Candidate::Init(std::string nm, std::string prt)
{
    name            = nm;
    party           = prt;
}

void Candidate::AssignBallot(Ballot* ballot)
{
    if (n_votes > 0)
    {
        // Add Ballot to the end of the linked list
        last_ballot->SetNext(ballot);
        last_ballot = ballot;
        n_votes += 1;
    }
    else
    {
        // If this is the first ballot, both ballot pointers will be null
        first_ballot = ballot;
        first_ballot->SetNext(ballot);
        last_ballot  = ballot;
        n_votes = 1;
    }
};

Ballot* Candidate::RemoveBallot()
{
    // Remove a Ballot object from this candidate's linked list
    Ballot* ret = first_ballot;
    first_ballot = ret->next;
    n_votes -= 1;
    return ret;
};

int Candidate::GetVoteCount()
{
    // Get the current number of votes belonging to this candidate
    return n_votes;
};

std::string Candidate::GetVoteIDs()
{
    // Get a comma separated string of all ballots belonging to this candidate
    std::string out = "";
    Ballot* temp = first_ballot;
    for (int idx_b = 0; idx_b<n_votes; idx_b++)
    {
        out += std::to_string(temp->GetID());
        out += ",";
        temp = temp->GetNext();
    }
    return out;
}