# Compiler
CPP = clang++

# Compiler flags
CPPFLAGS = -g -Wall -std=c++17

# Include path for Google Test headers
GTEST_INC = -I/opt/homebrew/include

# Library path and linking flags for Google Test
GTEST_LIB = -L/opt/homebrew/lib -lgtest -lgtest_main -pthread

# header files
HEADERS = scheduler.hpp ready_queue.hpp pcb.hpp

# Object files
OBJS = test.o

# Executable name
EXEC = simulate

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CPP) $(CPPFLAGS) $(GTEST_LIB) -o $(EXEC) test.o

# Compile test.cpp to test.o
test.o: test.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -c  $(GTEST_INC) test.cpp -o test.o

# Doxygen configuration file
DOXYFILE = Doxyfile

# Generate documentation
docs:
	doxygen $(DOXYFILE)

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Clean up documentation
clean_docs:
	rm -rf html latex

.PHONY: all clean docs clean_docs