# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Files
TARGET = $(BIN_DIR)/pfgrep
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Link object files into binary
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile each .cpp into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the program
run: all
	$(TARGET)
