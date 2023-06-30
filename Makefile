# Compiler
CXX = g++
CXXFLAGS = --std=c++17

# Directories
SRC_DIR = src
BIN_DIR = bin

# Executables
MAIN_EXE = main.out

# Sensitivity lists
MainExecutableSensitivityList =	\
	$(BIN_DIR)/main.o 			\
	$(BIN_DIR)/TCPReno.o 		\

MainSensitivityList = 			\
	$(SRC_DIR)/main.cpp 		\
	$(SRC_DIR)/TCPReno.hpp 		\

TCPRenoSensitivityList = 		\
	$(SRC_DIR)/TCPReno.cpp 		\
	$(SRC_DIR)/TCPReno.hpp 		\
	$(SRC_DIR)/defs.hpp 		\


# Compile
all: $(MAIN_EXE)

$(MAIN_EXE): $(MainExecutableSensitivityList)
	$(CXX) $(CXXFLAGS) $(MainExecutableSensitivityList) -o $(MAIN_EXE)


$(BIN_DIR)/main.o: $(MainSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(BIN_DIR)/main.o


$(BIN_DIR)/TCPReno.o: $(TCPRenoSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/TCPReno.cpp -o $(BIN_DIR)/TCPReno.o


# clean
.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*.o $(MAIN_EXE)
