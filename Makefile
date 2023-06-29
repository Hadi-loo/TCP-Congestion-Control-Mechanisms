# Compiler
CXX = g++
CXXFLAGS = --std=c++17 

# Directories
SRC_DIR = src
BIN_DIR = bin

# Executables
MAIN_EXE = main.out

# Objects


# Sensitivity lists
MainExecutableSensitivityList = \
	$(BIN_DIR)/main.o 			\
	$(BIN_DIR)/tcpreno.o		\

MainSensitivityList = 			\
	$(SRC_DIR)/main.cpp			\
	$(SRC_DIR)/TCPReno.hpp		\

TcprenoSensitivityList = 		\
	$(SRC_DIR)/TCPReno.cpp		\
	$(SRC_DIR)/TCPReno.hpp		\


# Compile
all: $(MAIN_EXE)

$(MAIN_EXE): $(MainExecutableSensitivityList)
	$(CXX) $(CXXFLAGS) $(MainExecutableSensitivityList) -o $(MAIN_EXE)


$(BIN_DIR)/main.o: $(MainSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(BIN_DIR)/main.o

$(BIN_DIR)/tcpreno.o: $(TcprenoSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/TCPReno.cpp -o $(BIN_DIR)/tcpreno.o


# Clean
.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*.o $(MAIN_EXE)