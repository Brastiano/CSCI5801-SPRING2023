# Compiler GNU C++
CXX = g++

# Flags to be used while compiling
# CXXFLAGS = -Wall -std=c++11 `pkg-config gtkmm-3.0 --cflags --libs`
CXXFLAGS = -Wall -std=c++11

#-DGUI_MODE=true `pkg-config gtkmm-3.0 --cflags --libs`

PACKAGE = `pkg-config gtkmm-3.0 --cflags --libs`

GUI_MODE = -DGUI_MODE

# Set up source files
SRC_DIR = ./src
GUI = $(SRC_DIR)/gui.cc
SRC = $(filter-out $(GUI),$(wildcard $(SRC_DIR)/*.cc))
SRC_OBJECTS = $(SRC:.cc = .o)
SRC_EXES = Tabulator
SRC_EXES_GUI = Tabulator_GUI

# Set up test files
TEST_DIR = ./testing
TEST = $(wildcard $(TEST_DIR)/*.cc)
TEST_OBJECTS = $(SRC:.cc = .o)

# Set up header files
HDR_DIR = ./src
HDR = $(wildcard $(HDR_DIR)/*.h)

# Default target
# How to use: Type `make` in terminal
all: $(SRC_EXES)

gui: $(SRC_EXES_GUI)

# Generate test executables
# How to use: Type `make test` in terminal
# test:	

# Document the code of whole system
# How to use: Type `make docs` in terminal
docs: $(HDR)
	@doxygen ./Doxyfile

$(SRC_EXES_GUI): $(SRC_OBJECTS) $(GUI)
	$(CXX) $(SRC_OBJECTS) $(GUI) -o $@ $(GUI_MODE) $(PACKAGE)

# Code for building an executable file
$(SRC_EXES): $(SRC_OBJECTS)
	$(CXX) $(SRC_OBJECTS) -o $@

# Specify the rules for building object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) $< -o $@

# Remove all object files and executable file in the CLI mode
# How to use: Type `make clean` in terminal
clean:
	rm -f *.o $(SRC_EXES)
	clear

# Remove all object files and executable file in the GUI mode
# How to use: Type `make clean_gui` in terminal
clean_gui:
	rm -f *.o $(SRC_EXES_GUI)
	clear

# Run the executable file
# How to use: Type `make run` in terminal
run: 
	./$(SRC_EXES)

# Run the executable file with timing
# How to use: Type `make time` in terminal
time: $(SRC_EXES)
	time -f "\nExecution time: %E\nCPU usage: %P\nMemory usage: %M KB\n" ./$(SRC_EXES)

run_gui:
	./$(SRC_EXES_GUI)
