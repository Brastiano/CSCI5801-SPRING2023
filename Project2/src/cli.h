/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Brian Bianchi, Andrew Brevick
 * File name: cli.h
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

#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <algorithm>
#include <unistd.h>

// Dummy class required for forward declaration
class Controller;

/**
 * @brief CLI (Command Line Interface) class. Primary function is to handle user/system interaction
 * 
 */
class Cli
{
    protected:
        /**
         * @brief Pointer to controller instance
         */
        Controller* controller_;

        /**
         * @brief Clears the Terminal/Console
         */
        void ClearConsole();

    public:
        /**
         * @brief Construct a new Cli object
         * 
         * @param controller controller instance to link with
         */
        Cli(Controller &controller);

        /**
         * @brief Destroy the Cli object
         * 
         */
        virtual ~Cli();

        /**
         * @brief Set the interface to Layout 1 (date and input file name entry)
         */
        void SetLayout1();

        /**
         * @brief Set the interface to Layout 1a (date and input file name entry) 
         * This is for multiple file input
         */
        bool SetLayout1a(std::string filenames[], int idx);

        /**
         * @brief Set the interface to Layout 2 (With IR parameters) (header display and user confirmation)
         * 
         * @param election_type String detailing the type of the election to be displayed ("IR"/"CPL")
         * @param num_candidates String to be displayed detailing the number of candidates
         * @param candidates String listing the candidates to be displayed
         * @param ballot_quantity String to be displayed detailing the number of ballots
         */
        void SetLayout2(std::string election_type,
                        std::string num_candidates,
                        std::string candidates,
                        std::string ballot_quantity,
                        std::string filenames[],
                        int n_files);

        /**
         * @brief Set the interface to Layout 2 (With CPL parameters) (header display and user confirmation)
         * 
         * @param election_type String detailing the type of the election to be displayed ("IR"/"CPL")
         * @param num_parties String to be displayed detailing the number of parties
         * @param parties String listing the parties to be displayed
         * @param seat_quantity String detailing the number of seats
         * @param ballot_quantity String to be displayed detailing the number of ballots
         */
        void SetLayout2(std::string election_type,
                        std::string num_parties,
                        std::string parties,
                        std::string seat_quantity,
                        std::string ballot_quantity,
                        std::string filenames[],
                        int n_files);

        /**
         * @brief Set the interface to Layout 3 (Loading screen)
         */
        void SetLayout3();

        /**
         * @brief Set the interface to Layout 4 (Results display)
         * 
         * @param top_text string containing overview of election held (formatted by the inputter, not the cli!)
         * @param bottom_text string containing election statistical breakdown (formatted by the inputter, not the cli!)
         */
        void SetLayout4(std::string top_text, std::string bottom_text);
};

#endif // CLI_H