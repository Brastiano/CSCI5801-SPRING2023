/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Andrew Brevick, Cuong Ha
 * File name: election.cc
 * Description: Parent class to be inherited by specific election strategies
 * @endcond
 */

#include "election.h"

Election::~Election() {
    // This one must be declared in source file to be runnable
    // Cannot do it in-line in header file
}

// "Fair" randomization based on methodology by mathematician John von Neumann
int Election::FlipCoin(int count) {
    while (true) {
        std::vector<int> counts(count);
        for (int i = 0; i < count; i ++) {
            counts.at((rand() + i) % count) += 1;
        }
        int max = 0;
        int num_maxes = 0;
        int max_index = count + 1;
        for (int n = 0; n < count; n++) {
            if (counts.at(n) > max) {
                max = counts.at(n);
                num_maxes = 1;
                max_index = n;
            } else if (counts.at(n) == max) {
                num_maxes += 1;
            }
        }
        if (num_maxes == 1) {
            return max_index;
        }
    }
};

int Election::CreateAuditFile() {
    audit_file.open(audit_name);

    if (!audit_file.is_open()) {
        return -1;
    }
    
    return 0;
};

int Election::WriteAuditFile(std::string write_data)
{
    audit_file << write_data;
    return 0;
};

void Election::SetFilePaths(std::string input_filename, std::string audit_filename)
{
    input_name = input_filename;
    audit_name = audit_filename;
    int audit_success = CreateAuditFile();
    input_file.open(input_name);
};