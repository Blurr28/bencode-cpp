# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Source Files
SRC = src/bencode_decoder.cpp src/bencode_encoder.cpp
TEST_SRC = test/test_bencode_encoder.cpp

# Object Files
OBJ = $(SRC:.cpp=.o) $(TEST_SRC:.cpp=.o)

# Target
TARGET = bencode_test

all: $(TARGET)

# Build Object Files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) -lboost_system

# Clean Build Files
clean:
	rm -f $(OBJ) $(TARGET)

# Run Tests
test: all
	./$(TARGET)
