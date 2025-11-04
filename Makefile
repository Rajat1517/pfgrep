CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lpthread

SRC_DIR = src
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/FileScanner.cpp $(SRC_DIR)/FileSearcher.cpp
TARGET = pfgrep

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
