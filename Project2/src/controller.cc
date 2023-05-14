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

Controller::Controller() {
    n_files = 1;
}

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

std::vector<std::string> Controller::GetBallotsNumber() {
    return ballots_number_;
}

void Controller::SetCli(Cli &cli, std::string arg_date, std::string arg_file_names[], int n_files) {
    cli_ = &cli;
    // Handles date and input filename as parameters and jumps ahead in the program if they are not empty
    std::cout << "Arg date: " << arg_date << "\nArg_names[0]" << arg_file_names[0] << "\n";
    if (arg_date != "" && arg_file_names[0] != "") {
        if (ReadElectionType(arg_file_names, arg_date, n_files)) { //Temp: Adjust 3rd argument
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
        for (int i = 0; i < n_files; i++) {
            input_file.open(input_file_names_[i]);
            if (!input_file.is_open()) {
                input_file_names_[i] = "testing/" + input_file_names_[i];
                input_file.open(input_file_names_[i]);
            }
            std::cout<<input_file.is_open()<<std::endl;
            std::getline(input_file, num_parties_);  // Skip first line
            std::getline(input_file, num_parties_);
            std::getline(input_file, parties_);
            std::string line;
            for (int i = 0; i < std::stoi(num_parties_); i++) {
                std::getline(input_file, line);
                candidates_ += line;
                candidates_ += "\n";
            }
            std::getline(input_file, seat_quantity_);
            std::string ballots_count_from_one_file;
            std::getline(input_file, ballots_count_from_one_file);
            ballots_number_.push_back(ballots_count_from_one_file);
            imported = true;
            input_file.close(); // Will be reopened in IR
        }

        // Get the number of ballots and convert it into integer !!!!! UPDATE COMMENT
        int total_ballots = 0;
        
        for (int i = 0; i < n_files; i++) {
            std::cout<<ballots_number_.at(i)<<std::endl;
        }
        
        for (int i = 0; i < n_files; i++) {
            total_ballots += std::stoi(ballots_number_.at(i));
        }

        input_file.close();
        /**
         * Reads file header, then progresses program flow to "stage 2" and transfers control authority to the interface
         * with a call to SetLayout2
         */
        #ifdef GUI_MODE
        gui_->SetLayout2(voting_method_, num_parties_, parties_, seat_quantity_, std::to_string(total_ballots));
        // gui_->SetLayout2(voting_method_, candidate_number_, candidates_, std::to_string(total_ballots));
        #else
        cli_->SetLayout2(voting_method_, num_parties_, parties_, seat_quantity_, std::to_string(total_ballots), input_file_names_, n_files);
        // cli_->SetLayout2(voting_method_, candidate_number_, candidates_, std::to_string(total_ballots), input_file_names_, n_files);

        #endif
    }
    //IR Header Parsing
    else {
        if (TEST_INPUT)
        {  
            for (int i = 0; i < n_files; i++) {
                input_file.open(input_file_names_[i]);
                if (!input_file.is_open()) {
                    input_file_names_[i] = "testing/" + input_file_names_[i];
                    input_file.open(input_file_names_[i]);
                }
                std::cout<<input_file.is_open()<<std::endl;
                if (!imported) {  // Meaning no information has been imported yet
                    std::getline(input_file, candidate_number_);  // Skip first line
                    std::getline(input_file, candidate_number_);
                    std::getline(input_file, candidates_);
                    std::string ballots_count_from_one_file;
                    std::getline(input_file, ballots_count_from_one_file);
                    ballots_number_.push_back(ballots_count_from_one_file);
                    imported = true;
                } else {  // Meaining at least one file has been imported and thus do not need to re-import the candidates              
                    std::string ballots_count_from_one_file;
                    // Skip first couple header lines
                    std::getline(input_file, ballots_count_from_one_file);
                    std::getline(input_file, ballots_count_from_one_file);
                    std::getline(input_file, ballots_count_from_one_file);

                    // Reach the line containing the number of ballots
                    std::getline(input_file, ballots_count_from_one_file);
                    ballots_number_.push_back(ballots_count_from_one_file);
                }
                input_file.close(); // Will be reopened in IR
            }
        }
        else
        {
            candidate_number_ = "4";
            candidates_ = "Kleinberg (R), Chou (I), Royce (L), Rosen (D)";
            ballots_number_ = {"6", "5"};
        }
        /**
         * Reads file header, then progresses program flow to "stage 2" and transfers control authority to the interface
         * with a call to SetLayout2
         */
        int total_ballots = 0;
        
        for (int i = 0; i < n_files; i++) {
            std::cout<<ballots_number_.at(i)<<std::endl;
        }
        
        for (int i = 0; i < n_files; i++) {
            total_ballots += std::stoi(ballots_number_.at(i));
        }
        #ifdef GUI_MODE
        gui_->SetLayout2(voting_method_, candidate_number_, candidates_, std::to_string(total_ballots));
        #else

        cli_->SetLayout2(voting_method_, candidate_number_, candidates_, std::to_string(total_ballots), input_file_names_, n_files);  

        #endif
    }
}


std::string Controller::HandleDateString(std::string date) {
    std::string new_date = date;
    std::replace(new_date.begin(), new_date.end(), '/', '_');
    std::replace(new_date.begin(), new_date.end(), '.', '_');
    return new_date;
}

bool Controller::ReadElectionType(std::string filenames[], std::string date, int num_files_in) {
    n_files = num_files_in;
    for (int idx = 0; idx<n_files; idx++)
    {
        input_file_names_[idx] = filenames[idx];
        std::cout << filenames[idx] <<"\n";
    }
    date_ = HandleDateString(date);


    if (TEST_INPUT)
    {
        // Verifies that the file can indeed be opened and identifies the election type
        input_file.open(input_file_names_[0]);
        if (!input_file.is_open()) {
            input_file_names_[0] = "testing/" + input_file_names_[0];
            input_file.open(input_file_names_[0]);
            if (!input_file.is_open()) {
                return false;
            }
        }
        getline(input_file, voting_method_);
        input_file.close();
    }
    else
    {
        voting_method_ = "IR";
    }
    return true;
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
    election_->SetFilePaths(input_file_names_, audit_file_name_);

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
        int b = std::stoi(ballots_number_.at(0));
        election_ = new IR(c, candidates_, b);
        if (TEST_VERBOSE) {std::cout << "Election type set to IR\n";}
    } else if (type == "CPL") {
        int num_parties = std::stoi(num_parties_);
        int num_seats = std::stoi(seat_quantity_);
        int num_ballots = std::stoi(ballots_number_.at(0));
        election_ = new CPL(num_parties, parties_, candidates_, num_seats, num_ballots);
    }
}
