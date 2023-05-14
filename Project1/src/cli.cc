/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Brian Bianchi
 * File name: cli.cc
 * Description: This file defines the methods for the CLI (Command Line Interface) for the system.
 *              It is made to mirror the functionality of the GUI (gui.cc) for ease of integration
 *              with the rest of the system. To this end, the key functions:
 *              - SetLayout1()
 *              - SetLayout2()
 *              - SetLayout3()
 *              - SetLayout4()
 *              Share the same overall functionality and parameters with their GUI counterparts.
 *              These functions handle display of information, user input, and, alongside the
 *              Controller (controller.cc), the program control flow.
 * @endcond
 */

#include "cli.h"
// controller.h must be included here rather than in header because forward declaration is required
// for CLI and Controller to be codependent
#include "controller.h" 

// The CLI is useless without an instance of controller to coordinate with
Cli::Cli(Controller &controller) {
    controller_ = &controller;
}

// Both the CLI and the controller are present for the entirety of program execution; no destruction needed
Cli::~Cli() {}

void Cli::SetLayout1()
{
    std::string layout_1_header =   "#=========================#\n"
                                    "# Election File Selection #\n"
                                    "#=========================#\n\n";
    std::string prompt_1 =  "Please enter the date of the election (in mm-dd-yyyy format)\n\n";
    std::string prompt_2 =  "\nPlease enter the name of the election results file to load.\n"
                            "The file should be in the same folder as this application.\n"
                            "Please include any file extensions at the end of the name\n"
                            "(.txt, .csv, and so on).\n\n";
    ClearConsole();
    std::cout << layout_1_header << prompt_1;
    std::string date = "";
    std::cin >> date;
    std::cout << prompt_2;
    std::string filename = "";
    std::cin >> filename;
    /**
     * The controller is queried to read the beginning of the input file. If that succeeds, controller is
     * put in control of the program flow to read the full header information and proceed as it determines
     * to from there. If the read fails, the user is informed that the file was invalid and the program
     * loops to the beginning of this function to receive fresh input.
     */ 
    if (controller_->ReadElectionType(filename, date) == 0) {
        controller_->ReadHeader();
    } else {
        std::cout << "\nUnable to open file! Please re-enter..." << std::endl;
        sleep(2);
        SetLayout1();
    }
}

// IR
void Cli::SetLayout2(   std::string election_type, std::string num_candidates,
                        std::string candidates, std::string ballot_quantity)
{
    std::string layout_2_header =   "#======================#\n"
                                    "# Election Information #\n"
                                    "#======================#\n\n";
    std::string header =    "Election Type: " + election_type +
                            "\nNumber of Candidates: " + num_candidates +
                            "\nCandidates: " + candidates +
                            "\nBallot Quantity: " + ballot_quantity;
    std::string prompt_3 =  "\nConfirm processing of this file with \"Yes\" or \"Y\" (not case sensitive).\n"
                            "Return to file selection with any other input.\n\n";
    ClearConsole();
    std::cout << layout_2_header << header << std::endl;
    std::cout << prompt_3;
    std::string response;
    std::cin >> response;
    // Lowercases the user input string for simpler handling
    std::transform(response.begin(), response.end(), response.begin(), ::tolower);
    /**
     * If yes is entered, the flow of control is granted to the controller once more to process the election.
     * Otherwise, the program cycles to the beginning with SetLayout1().
    */
    if (response == "yes" || response == "y") {
        controller_->ProcessElection();
    }
    else {
        SetLayout1();
    }
}

// CPL
void Cli::SetLayout2(   std::string election_type, std::string num_parties,
                        std::string parties, std::string seat_quantity, std::string ballot_quantity)
{
    std::string layout_2_header =   "#======================#\n"
                                    "# Election Information #\n"
                                    "#======================#\n\n";
    std::string header =    "Election Type: " + election_type +
                            "\nNumber of Parties: " + num_parties +
                            "\nParties: " + parties +
                            "\nNumber of Seats: " + seat_quantity +
                            "\nNumber of Ballots: " + ballot_quantity;
    std::string prompt_3 =  "\nConfirm processing of this file with \"Yes\" or \"Y\" (not case sensitive).\n"
                            "Return to file selection with any other input.\n\n";
    ClearConsole();
    std::cout << layout_2_header << header << std::endl;
    std::cout << prompt_3;
    std::string response;
    std::cin >> response;
    // Lowercases the user input string for simpler handling
    std::transform(response.begin(), response.end(), response.begin(), ::tolower);
    /**
     * If yes is entered, the flow of control is granted to the controller once more to process the election.
     * Otherwise, the program cycles to the beginning with SetLayout1().
    */
    if (response == "yes" || response == "y") {
        controller_->ProcessElection();
    }
    else {
        SetLayout1();
    }
}

void Cli::SetLayout3()
{
    std::string layout_3_header =   "#===========================#\n"
                                    "# Tabulation in progress... #\n"
                                    "#===========================#\n\n";
    ClearConsole();
    std::cout << layout_3_header;
}

void Cli::SetLayout4(std::string top_text, std::string bottom_text)
{
    std::string layout_4_header =   "#=========#\n"
                                    "# Results #\n"
                                    "#=========#\n\n";
    ClearConsole();
    std::cout << layout_4_header;
    std::cout << top_text << std::endl << std::endl;
    std::cout << bottom_text << std::endl;
    // Represents the end of the program, no more instructions given
}

void Cli::ClearConsole()
{
    std::cout << std::endl;
    // Different systems use different commands, this utilizes either as needed
    if (system("cls"))
    {
        system("clear");
    }
}