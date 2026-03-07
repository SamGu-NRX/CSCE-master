# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g
LDFLAGS =

# Target executable
TARGET = lms

# Source and object files
SRCS = main.cpp \
       AudioCD.cpp Books.cpp DVD.cpp LibraryItems.cpp \
       LibraryItemsCollection.cpp Loans.cpp LoansCollection.cpp \
       Patron.cpp PatronsCollection.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Linking target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilation rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
