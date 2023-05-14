/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Andrew Brevick, Brian Bianchi, Cuong Ha
 * File name: controller.h
 * Description: manages inteactions between user interface and election processing
 * @endcond
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include <fstream>

#include "election.h"
#include "ir.h"
#include "cpl.h"

// Includes the gtkmm libraries if GUI mode is enabled (can cause systems without to crash!)
// Lines ignored if GUI_MODE is not enabled, allowing safer compilation
#ifdef GUI_MODE
#include <gtkmm/application.h>
#include <gtkmm/application.h>
#endif

#define TEST_INPUT 1
#define TEST_VERBOSE 1

// Dummy Interface classes, required for forward declaration
#ifdef GUI_MODE
class Gui;
#endif

class Cli;

/**
 * @brief Controller class. Manages inteactions between user interface and election processing
 * 
 */
class Controller
{
private:
    // Generic
    /**
     * @brief String of election type (voting method) from inputted election file
     */
    std::string voting_method_;

    /**
     * @brief String of user inputted date used in the naming of the audit file
     */
    std::string date_;

    #ifdef GUI_MODE
    /**
     * @brief Pointer to Gui instance
     */
    Gui* gui_;
    #endif
    /**
     * @brief Pointer to Cli instance
     */
    Cli* cli_;

    /**
     * @brief Pointer to Election instance (defaults to null)
     */
    Election *election_ = NULL;

    /**
     * @brief Recurringly used file stream for the user-inputted file
     */
    std::ifstream input_file;

    /**
     * @brief Determines the name of the Audit File based on date_ and voting_method_
     * 
     * @return std::string audit file name
     */
    std::string AuditName();

    /**
     * @brief Creates new election object specific to its type, assigns to election_
     * 
     * @param type string designating election type
     */
    void SetElectionType(std::string type);

    /**
     * @brief String of inputted election file
     */
    std::string input_file_name_;
    
    // IR
    /**
     * @brief String of IR candidate number as read from file header
     */
    std::string candidate_number_;

    /**
     * @brief String of IR candidates list as read from file header
     */
    std::string candidates_;

    /**
     * @brief String of IR ballots number as read from file header
     */
    std::string ballots_number_;

    // CPL
    /**
     * @brief String of CPL party number as read from file header
     */
    std::string num_parties_;

    /**
     * @brief String of CPL parties list as read from file header
     */
    std::string parties_;

    /**
     * @brief String of CPL seat number as read from file header
     */
    std::string seat_quantity_;

    /**
     * @brief String of CPL ballot number as read from file header
     */
    std::string ballot_quantity_;

public:
    /**
     * @brief Construct a new Controller object
     */
    Controller();

    /**
     * @brief Destroy the Controller object and the election instance with it
     */
    ~Controller();

    #ifdef GUI_MODE
    /**
     * @brief Set the pointer to the GUI object and take in optional string
     * parameters for run arguments with input file name and date already entered
     * 
     * @param gui gui instance to link with
     * @param arg_date optional string for command argument for date, can be empty ("")
     * @param arg_file_name optional string for command argument for input file name, can be empty ("")
     */
    void SetGui(Gui &gui, std::string arg_date, std::string arg_file_name);
    #endif

    /**
     * @brief Set the pointer to the CLI object and take in optional string
     * parameters for run arguments with input file name and date already entered
     * 
     * @param cli cli instance to link with
     * @param arg_date optional string for command argument for date, can be empty ("")
     * @param arg_file_name optional string for command argument for input file name, can be empty ("")
     */
    void SetCli(Cli &cli, std::string arg_date, std::string arg_file_name);

    /**
     * @brief Verifies the user inputted file can be opened and reads the first line from the file (designating the election type)
     * 
     * @param filename user inputted filename to attempt to open
     * @param date user inputted date to save in controller for later
     * @return int 0 on success, -1 on failure
     */
    int ReadElectionType(std::string filename, std::string date);

    /**
     * @brief Reads header for election file, depending on election mode, and passes information to interface
     */
    void ReadHeader();

    /**
     * @brief Sets loading screen, creates election object based on previously gleaned information, signals election object
     * to process the election, and calls interface to display results
     */
    void ProcessElection();
};

#endif // CONTROLLER_H