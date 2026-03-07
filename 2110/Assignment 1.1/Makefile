CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Simple single-file version (matches requirements exactly)
SIMPLE_TARGET = library_system
SIMPLE_SRC = library_system.cpp

# Multi-file OOP version (with classes)
OOP_TARGET = library_management
OOP_SRCS = main.cpp Book.cpp Library.cpp
OOP_OBJS = $(OOP_SRCS:.cpp=.o)
OOP_HEADERS = Book.h Library.h

# GoogleTest configuration
GTEST_DIR = ../googletest-v1.17.0/googletest
GTEST_HEADERS = $(GTEST_DIR)/include
GTEST_LIB = libgtest.a
TEST_TARGET = run_tests

# Default: build simple version
all: $(SIMPLE_TARGET)

# Simple single-file version
$(SIMPLE_TARGET): $(SIMPLE_SRC)
	$(CXX) $(CXXFLAGS) -o $(SIMPLE_TARGET) $(SIMPLE_SRC)

# OOP multi-file version
oop: $(OOP_TARGET)

$(OOP_TARGET): $(OOP_OBJS)
	$(CXX) $(CXXFLAGS) -o $(OOP_TARGET) $(OOP_OBJS)

%.o: %.cpp $(OOP_HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build GoogleTest library
$(GTEST_LIB): $(GTEST_DIR)/src/gtest-all.cc $(GTEST_DIR)/src/gtest_main.cc
	$(CXX) $(CXXFLAGS) -isystem $(GTEST_HEADERS) -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	$(CXX) $(CXXFLAGS) -isystem $(GTEST_HEADERS) -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest_main.cc
	ar -rv $(GTEST_LIB) gtest-all.o gtest_main.o

# Build and run tests (for OOP version)
$(TEST_TARGET): $(GTEST_LIB) Book.o Library.o tests/library_test.o
	$(CXX) $(CXXFLAGS) -isystem $(GTEST_HEADERS) -pthread Book.o Library.o tests/library_test.o $(GTEST_LIB) -o $(TEST_TARGET)

tests/library_test.o: tests/library_test.cpp $(OOP_HEADERS)
	$(CXX) $(CXXFLAGS) -isystem $(GTEST_HEADERS) -c tests/library_test.cpp -o tests/library_test.o

test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run simple version
run: $(SIMPLE_TARGET)
	./$(SIMPLE_TARGET)

# Run OOP version
run-oop: $(OOP_TARGET)
	./$(OOP_TARGET)

clean:
	rm -f $(SIMPLE_TARGET) $(OOP_TARGET) $(TEST_TARGET) $(OOP_OBJS) tests/*.o *.o $(GTEST_LIB) gtest-all.o gtest_main.o

.PHONY: all oop test run run-oop clean
