/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Brian Bianchi
 * File name: gui.cc
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

#include "gui.h"
#include <iostream>
// controller.h must be included here rather than in header because forward declaration is required
// for GUI and Controller to be codependent
#include "controller.h"

// For the non-specifically-linear flow of the GUI, each UI object must be initialized and configured
// early on, even if it is not used/shown until later.
Gui::Gui(Controller &controller, std::string arg_date, std::string arg_file_name) {
    controller_ = &controller;

    // Setting overall window settings
    set_title("Election Tabulation Software");
    set_border_width(10);
    set_default_size(700, 350);
    set_mnemonics_visible(true);

    // interface_ acts as a container for the layouts, as the window itself can only have one widget
    interface_.set_orientation(Gtk::ORIENTATION_VERTICAL);
    add(interface_);

    // LAYOUT 1
    layout_1_.set_orientation(Gtk::ORIENTATION_VERTICAL);

    text_title_1_.set_markup("<big>Election File Selection</big>");
    text_title_1_.set_justify(Gtk::Justification::JUSTIFY_CENTER);
    layout_1_.pack_start(text_title_1_);
    text_title_1_.show();

    text_instruction_.set_markup("Please enter the date of the election (in mm-dd-yyyy format)"
                                " in the top box and then enter the name of the election results"
                                " file to load. This file should be in the same folder as this"
                                " application. Please include any file extensions at the end of"
                                " the name (.txt, .csv, and so on).");
    text_instruction_.set_line_wrap(true);
    layout_1_.pack_start(text_instruction_);
    text_instruction_.show();

    input_election_date_.set_text("Enter Election Date Here (mm-dd-yyyy)");
    layout_1_.pack_start(input_election_date_);
    input_election_date_.show();

    input_election_file_.set_text("Enter File Name Here");
    layout_1_.pack_start(input_election_file_);
    input_election_file_.show();

    button_confirm_1_.set_label("_Confirm");
    button_confirm_1_.set_use_underline(true);
    button_confirm_1_.signal_clicked().connect( sigc::mem_fun(*this, &Gui::OnConfirm1) );
    layout_1_.pack_start(button_confirm_1_);
    button_confirm_1_.show();

    interface_.pack_start(layout_1_);

    //LAYOUT 2
    layout_2_.set_orientation(Gtk::ORIENTATION_VERTICAL);

    text_title_2_.set_markup("<big>Election Information</big>");
    text_title_2_.set_justify(Gtk::Justification::JUSTIFY_CENTER);
    layout_2_.pack_start(text_title_2_);
    text_title_2_.show();
    
    text_header_.set_text("Header Info");
    layout_2_.pack_start(text_header_);
    text_header_.show();

    button_return_.set_label("_Back to File Selection");
    button_return_.set_use_underline(true);
    button_return_.signal_clicked().connect( sigc::mem_fun(*this, &Gui::OnReturn) );
    layout_2_.pack_start(button_return_);
    button_return_.show();

    button_confirm_2_.set_label("_Confirm");
    button_confirm_2_.set_use_underline(true);
    button_confirm_2_.signal_clicked().connect( sigc::mem_fun(*this, &Gui::OnConfirm2) );
    layout_2_.pack_start(button_confirm_2_);
    button_confirm_2_.show();

    interface_.pack_start(layout_2_);

    // LAYOUT 3
    layout_3_.set_orientation(Gtk::ORIENTATION_VERTICAL);

    text_title_3_.set_markup("<big>Tabulation in progress...</big>");
    text_title_3_.set_justify(Gtk::Justification::JUSTIFY_CENTER);
    layout_3_.pack_start(text_title_3_);
    text_title_3_.show();

    interface_.pack_start(layout_3_);

    // LAYOUT 4
    layout_4_.set_orientation(Gtk::ORIENTATION_VERTICAL);

    text_title_4_.set_markup("<big>Results</big>");
    text_title_4_.set_justify(Gtk::Justification::JUSTIFY_CENTER);
    layout_4_.pack_start(text_title_4_);
    text_title_4_.show();

    text_overview_.set_markup("Top Results");
    layout_4_.pack_start(text_overview_);
    text_overview_.show();

    text_table_.set_markup("table");
    layout_4_.pack_start(text_table_);
    text_table_.show();

    button_exit_.set_label("_Exit");
    button_exit_.set_use_underline(true);
    button_exit_.signal_clicked().connect( sigc::mem_fun(*this, &Gui::OnExit) );
    layout_4_.pack_start(button_exit_);
    button_exit_.show();

    // If either the arg_date or the arg_file_name is not entered, then proceed as normal to setting layout to 1.
    // Otherwise, do not proceed to setting layout 1, as there are parameters to handle (which Controller will handle
    // after this gui constructor is complete)
    interface_.pack_start(layout_4_);
    if (arg_date == "" || arg_file_name == "") {
        SetLayout1();
    }
    
}

Gui::~Gui() {}

void Gui::SetLayout1()
{
    layout_2_.hide();
    layout_3_.hide();
    layout_4_.hide();
    layout_1_.show();
    interface_.show();
}

// IR
void Gui::SetLayout2(   std::string election_type, std::string num_candidates,
                        std::string candidates, std::string ballot_quantity)
{
    layout_1_.hide();
    layout_3_.hide();
    layout_4_.hide();
    std::string header =    "Election Type: " + election_type +
                            "\nNumber of Candidates: " + num_candidates +
                            "\nCandidates: " + candidates +
                            "\nBallot Quantity: " + ballot_quantity;
    text_header_.set_text(header);
    text_header_.set_justify(Gtk::Justification::JUSTIFY_LEFT);
    layout_2_.show();
    interface_.show();
}

// CPL
void Gui::SetLayout2(   std::string election_type, std::string num_parties,
                        std::string parties, std::string seat_quantity, std::string ballot_quantity)
{
    layout_1_.hide();
    layout_3_.hide();
    layout_4_.hide();
    std::string header =    "Election Type: " + election_type +
                            "\nNumber of Parties: " + num_parties +
                            "\nParties: " + parties +
                            "\nNumber of Seats: " + seat_quantity +
                            "\nNumber of Ballots: " + ballot_quantity;
    text_header_.set_text(header);
    text_header_.set_justify(Gtk::Justification::JUSTIFY_LEFT);
    layout_2_.show();
    interface_.show();
}

void Gui::SetLayout3()
{
    layout_1_.hide();
    layout_2_.hide();
    layout_4_.hide();
    layout_3_.show();
    interface_.show();
}

void Gui::SetLayout4(std::string top_text, std::string bottom_text)
{
    layout_1_.hide();
    layout_2_.hide();
    layout_3_.hide();
    text_overview_.set_text(top_text);
    text_table_.set_text(bottom_text);
    text_table_.set_justify(Gtk::Justification::JUSTIFY_LEFT);
    layout_4_.show();
    interface_.show();
}

void Gui::OnConfirm1()
{
    /**
     * The controller is queried to read the beginning of the input file. If that succeeds, controller is
     * put in control of the program flow to read the full header information and proceed as it determines
     * to from there. If the read fails, the user is informed that the file was invalid and the interface state
     * is set back to SetLayout1().
     */ 
    if (controller_->ReadElectionType(input_election_file_.get_text(), input_election_date_.get_text()) == 0) {
        controller_->ReadHeader();
    } else {
        std::cout << "\nUnable to open file! Please re-enter..." << std::endl;
        sleep(2);
        SetLayout1();
    }
}

void Gui::OnReturn()
{
    SetLayout1();
}

void Gui::OnConfirm2()
{
    controller_->ProcessElection();
}

void Gui::OnExit()
{
    get_application()->quit();
}