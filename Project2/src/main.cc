/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Brian Bianchi, Andrew Brevick
 * File name: main.cc
 * Description: The main function which takes in parameters, determines the mode
 *              to run the program in (GUI or CLI), instantiates the appropriate
 *              classes, and runs the program.
 * @endcond
 */

#include <iostream>
#include <time.h>
#include "controller.h"
#include "cli.h"

/**
 * This flag GUI_MODE is set by the makefile/in compilation instructions.
 * Enabled, it will import GUI libraries and run the GUI version of the program.
 * Without the compiler guards, the code would not compile on machines without
 * GTKMM (such as the lab machines at the time of writing).
 */
#ifdef GUI_MODE
#include "gui.h"
#endif

/**
 * gui/cli and controller are codependent classes. As this is not a multithreaded program,
 * the "main line of operation" is routinely transferred between them, requiring each have
 * a reference to the instance of the other.
 */
int main(int argc, char* argv[]) {
    srand(time(NULL));
    std::string arg_date = "";
    int n_files_ = argc - 2;
    if (n_files_<1) {n_files_ = 1;}
    std::string arg_names[10];
    if (argc >= 2) {
        std::cout << "N files is:" << n_files_ << "\n";
        arg_date = argv[1];
        arg_names[n_files_];
        for(int i = 0; i< n_files_; i++)
        {
            arg_names[i] = argv[i+2];
            std::cout << arg_names[i] << "\n";
        }
    }
    else { arg_names[1] = {""};}
    Controller controller;
    #ifdef GUI_MODE
    std::cout << "GUI ENABLED" << std::endl;
    auto app = Gtk::Application::create("umn.csci5801.group21.tabulator");
    Gui gui(controller, arg_date, arg_names);
    controller.SetGui(gui, arg_date, arg_names);
    return app->run(gui);
    #else
    Cli cli(controller);
    std::cout << arg_date << "\n";
    std::cout << arg_names[0] << "\n";
    controller.SetCli(cli, arg_date, arg_names, n_files_);
    #endif
}