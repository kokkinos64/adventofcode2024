# Compiler and flags
CXX = g++
CXXFLAGS = -g3 -Wall -Wextra -std=c++17

# Target executable name
TARGET = run

# Find all .cpp files in the current directory
SRCS = $(wildcard *.cpp)

# Corresponding object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link objects to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp file to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run valgrind on the executable
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean valgrind