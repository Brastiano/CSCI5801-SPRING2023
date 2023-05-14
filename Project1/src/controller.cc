/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Andrew Brevick, Brian Bianchi, Cuong Ha
 * File name: controller.cc
 * Description: manages inteactions between user interface and election processing
 * @endcond
 */

#include "controller.h"
#include "cli.h"
#ifdef GUI_MODE
#include "gui.h"
#endif

Controller::Controller() {}

Controller::~Controller() {
    delete election_;
}

#ifdef GUI_MODE
void Controller::SetGui(Gui &gui, std::string arg_date, std::string arg_file_name) {
    gui_ = &gui;
    // Handles date and input filename as parameters and jumps ahead in the program if they are not empty
    if (arg_date != "" && arg_file_name != "") {
        if (ReadElectionType(arg_file_name, arg_date) == 0) {
            ReadHeader();
        } else {
            // Transfers control flow to interface to display the first layout
            gui_->SetLayout1();
        }
    } else {
        // Transfers control flow to interface to display the first layout
        gui_->SetLayout1();
    }
}
#endif

void Controller::SetCli(Cli &cli, std::string arg_date, std::string arg_file_name) {
    cli_ = &cli;
    // Handles date and input filename as parameters and jumps ahead in the program if they are not empty
    if (arg_date != "" && arg_file_name != "") {
        if (ReadElectionType(arg_file_name, arg_date) == 0) {
            ReadHeader();
        } else {
            // Transfers control flow to interface to display the first layout
            cli_->SetLayout1();
        }
    } else {
        // Transfers control flow to interface to display the first layout
        cli_->SetLayout1();
    }
}

void Controller::ReadHeader() {
    // CPL Header Parsing
    if (voting_method_ == "CPL") {        
        std::string line;
        // Get total number of parties and convert it into integer
        std::getline(input_file, num_parties_);
        
        // Get the parties
        std::getline(input_file, parties_);
        
        // Get the candidates
        candidates_ = "";
        for (int i = 0; i < std::stoi(num_parties_); i++) {
            std::getline(input_file, line);
            candidates_ += line;
            candidates_ += "\n";
        }

        // Get the number of seats and convert it into integer
        std::getline(input_file, seat_quantity_);

        // Get the number of ballots and convert it into integer
        std::getline(input_file, ballot_quantity_);

        input_file.close();
        /**
         * Reads file header, then progresses program flow to "stage 2" and transfers control authority to the interface
         * with a call to SetLayout2
         */
        #ifdef GUI_MODE
        gui_->SetLayout2("CPL", num_parties_, parties_, seat_quantity_, ballot_quantity_);
        #else
        cli_->SetLayout2("CPL", num_parties_, parties_, seat_quantity_, ballot_quantity_);
        #endif
    }
    //IR Header Parsing
    else {
        if (TEST_INPUT)
        {
            std::getline(input_file, candidate_number_);
            std::getline(input_file, candidates_);
            std::getline(input_file, ballots_number_);

            input_file.close(); // Will be reopened in IR
        }
        else
        {
            candidate_number_ = "4";
            candidates_ = "Kleinberg (R), Chou (I), Royce (L), Rosen (D)";
            ballots_number_ = "6";
        }
        /**
         * Reads file header, then progresses program flow to "stage 2" and transfers control authority to the interface
         * with a call to SetLayout2
         */
        #ifdef GUI_MODE
        gui_->SetLayout2(voting_method_, candidate_number_, candidates_, ballots_number_);
        #else
        cli_->SetLayout2(voting_method_, candidate_number_, candidates_, ballots_number_);  
        #endif
    }
}

int Controller::ReadElectionType(std::string filename, std::string date) {
    input_file_name_ = filename;
    date_ = date;

    if (TEST_INPUT)
    {
        // Verifies that the file can indeed be opened and identifies the election type
        input_file.open(input_file_name_);
        if (!input_file.is_open()) {
            input_file_name_ = "testing/" + input_file_name_;
            input_file.open(input_file_name_);
            if (!input_file.is_open()) {
                return -1;
            }
        }
        getline(input_file, voting_method_);
    }
    else
    {
        voting_method_ = "IR";
    }
    return 0;
}

void Controller::ProcessElection() {
    // Sets the Interface to layout 3, which is a loading screen, then proceeds to process the election
    #ifdef GUI_MODE
    gui_->SetLayout3();
    #else
    cli_->SetLayout3();
    #endif
    // Do stuff like instantiate election and fill in the type
    // then do the tabulation and stuff
    // when that is all done, then move to layout 4 and pass in results
    std::string results_top = "";
    std::string results_table = "";
    SetElectionType(voting_method_);
    std::string audit_file_name_ = AuditName();
    election_->SetFilePaths(input_file_name_, audit_file_name_);

    election_->ProcessElection(results_top, results_table);

    /**
     * Election is processed, only thing left to do is wrap up by sending the interface results information for
     * it to display
     */
    #ifdef GUI_MODE
    gui_->SetLayout4(results_top, results_table);
    #else
    cli_->SetLayout4(results_top, results_table);
    #endif
}

std::string Controller::AuditName()
{
    // Example Audit File Name: "audit_file_IR_3-26-2023.txt"
    std::string audit_file_name = "audit_file_" + voting_method_ + "_" + date_ + ".txt";
    return audit_file_name;
}

void Controller::SetElectionType(std::string type)
{
    if (election_ != NULL) delete election_;
    if (type == "IR") {
        int c = std::stoi(candidate_number_);
        int b = std::stoi(ballots_number_);
        election_ = new IR(c, candidates_, b);
        if (TEST_VERBOSE) {std::cout << "Election type set to IR\n";}
    } else if (type == "CPL") {
        int num_parties = std::stoi(num_parties_);
        int num_seats = std::stoi(seat_quantity_);
        int num_ballots = std::stoi(ballot_quantity_);
        election_ = new CPL(num_parties, parties_, candidates_, num_seats, num_ballots);
    }
}

