/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Brian Bianchi
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
    std::string arg_name = "";
    if (argc == 3) {
        arg_date = argv[1];
        arg_name = argv[2];
    }
    Controller controller;
    #ifdef GUI_MODE
    std::cout << "GUI ENABLED" << std::endl;
    auto app = Gtk::Application::create("umn.csci5801.group21.tabulator");
    Gui gui(controller, arg_date, arg_name);
    controller.SetGui(gui, arg_date, arg_name);
    return app->run(gui);
    #else
    Cli cli(controller);
    controller.SetCli(cli, arg_date, arg_name);
    #endif
}