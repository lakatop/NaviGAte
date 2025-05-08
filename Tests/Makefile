# Variables
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O3
TARGET = tests
SRC = tests.cpp

# Build target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean
clean:
	rm -f $(TARGET)