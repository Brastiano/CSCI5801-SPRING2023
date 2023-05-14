/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Brian Bianchi
 * File name: gui.h
 * Description: This file defines the methods for the GUI (Graphical User Interface) for the system.
 *              It is made to mirror the functionality of the CLI (cli.cc) for ease of integration
 *              with the rest of the system. To this end, the key functions:
 *              - SetLayout1()
 *              - SetLayout2()
 *              - SetLayout3()
 *              - SetLayout4()
 *              Share the same overall functionality and parameters with their CLI counterparts.
 *              These functions handle display of information, user input, and, alongside the
 *              Controller (controller.cc), the program control flow.
 * @endcond
 */

#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <unistd.h>

// Dummy class required for forward declaration
class Controller;

/**
 * @brief GUI (Graphical User Interface) class. Primary function is to handle user/system interaction graphically
 * 
 */
class Gui : public Gtk::Window
{
    protected:
        /**
         * @brief Handles confirm button press from layout 1
         */
        void OnConfirm1();

        /**
         * @brief Handles return button press from layout 2
         */
        void OnReturn();

        /**
         * @brief Handles confirm button press from layout 2
         */
        void OnConfirm2();

        /**
         * @brief Handles exit button press from layout 4
         */
        void OnExit();

        /**
         * @brief Pointer to controller instance
         */
        Controller* controller_;

        /**
         * @brief GTKMM Widget Box Instances - act as containers for other widgets
         */
        Gtk::Box interface_, layout_1_, layout_2_, layout_3_, layout_4_;

        /**
         * @brief GTKMM Widget Button Instances - Process presses
         */
        Gtk::Button button_confirm_1_, button_confirm_2_, button_return_, button_exit_;

        /**
         * @brief GTKMM Widget Entry Instances - take in user input
         */
        Gtk::Entry input_election_date_, input_election_file_;

        /**
         * @brief GTKMM Widget Label Instances - Display text
         */
        Gtk::Label text_title_1_, text_title_2_, text_title_3_,
            text_title_4_, text_instruction_, text_header_, text_overview_, text_table_;

    public:
        /**
         * @brief Construct a new Gui object
         * 
         * @param controller controller instance to link with
         * @param arg_date string with optional launch argument for date
         * @param arg_file_name string with optional launch argument for input file name
         */
        Gui(Controller &controller, std::string arg_date, std::string arg_file_name);

        /**
         * @brief Destroy the Gui object
         * 
         */
        virtual ~Gui();

        /**
         * @brief Set the interface to Layout 1 (date and input file name entry)
         */
        void SetLayout1();

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
                        std::string ballot_quantity);

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
                        std::string ballot_quantity);

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

#endif // GUI_H