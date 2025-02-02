CXX = g++
CXXFLAGS = --std=c++17 -Iinclude -Wall
SRC = src/BencodeDecoder.cpp
TEST_SRC = test/testBencodeDecoder.cpp
TARGET = test_bencode

all: $(TARGET)

$(TARGET): $(Src) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(TEST_SRC) -lboost_system

clean:
	rm -f $(TARGET)
