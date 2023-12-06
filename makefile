CXX = g++
CXXFLAGS = -std=c++17
SRC_DIR = ./src
OBJ_DIR = .
BIN_DIR = .

# List of source files
SRCS = $(SRC_DIR)/Bond.cpp $(SRC_DIR)/BondAsset.cpp $(SRC_DIR)/Controller.cpp $(SRC_DIR)/csviostream.cpp $(SRC_DIR)/Portfolio.cpp $(SRC_DIR)/PortfolioManager.cpp $(SRC_DIR)/prettyprintutils.cpp $(SRC_DIR)/Security.cpp $(SRC_DIR)/User.cpp 

# Generate the list of object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# The name of the final executable
TARGET = $(BIN_DIR)/BondPortfolioWizard

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#$(OBJ_DIR):
#	mkdir -p $(OBJ_DIR)

#$(BIN_DIR):
#	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) #$(BIN_DIR)

.PHONY: all clean


