

#include"ir.h"
#include<iostream>
#include<string>
#include<fstream>



/*int main()
{
    std::string all_cand = "Bob (R), Candy (D), Jane (I)";

    std::string input_filename = "../testing/IR_input_test_4.csv";
    std::string audit_filename = "IR_audit_test.txt";
    std::ifstream input_file;
    input_file.open(input_filename);
    if (!input_file.is_open()) {std::cout << "Could not open file\n";}

    std::string candidate_number_, candidates_, ballots_number_, voting_method_;
    std::cout << "Reading Header\n";
    std::getline(input_file, voting_method_);
    std::cout << voting_method_ << "\n";
    std::getline(input_file, candidate_number_);
    std::cout << candidate_number_ << "\n";
    std::getline(input_file, candidates_);
    std::cout << candidates_ << "\n";
    std::getline(input_file, ballots_number_);
    std::cout << ballots_number_ << "\n";

    int n_candidates, n_ballots;
    n_candidates = std::stoi(candidate_number_);
    //n_candidates = 4;
    //n_ballots = 1080;
    n_ballots = std::stoi(ballots_number_);
    Election* election_;
    election_ = new IR(n_candidates, candidates_, n_ballots);

    std::cout<< "Setting File Paths\n";
    election_->SetFilePaths(input_filename, audit_filename);


    std::string results_top, results_table;
    std::cout << "Processing Election\n";
    election_->ProcessElection(results_top, results_table);

    std::cout << results_top;
    std::cout << "\n\n" << results_table;

    
    return 0;
};*/

