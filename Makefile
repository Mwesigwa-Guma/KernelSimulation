# Compiler
CLANG = clang++

# Compiler flags
CLANGFLAGS = -g -Wall -std=c++17

# Include path for Google Test PROCESSHEADERS
GTEST_INC = -I/opt/homebrew/include

# Library path and linking flags for Google Test
GTEST_LIB = -L/opt/homebrew/lib -lgtest -lgtest_main -pthread

# header files
PROCESSHEADERS = ProcessScheduling/scheduler.hpp ProcessScheduling/ready_queue.hpp ProcessScheduling/pcb.hpp ProcessScheduling/message_queue.hpp

# thread headers
THREADHEADERS = ThreadManager/ThreadManager.hpp ThreadManager/threadReadyQueue.hpp

# Object files
OBJS = test.o scheduler.o processschedulingtests.o threadmanager.o threadmanagertests.o

# Executable name
EXEC = simulate

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CLANG) $(CLANGFLAGS) $(GTEST_LIB) -o $(EXEC) $(OBJS)

# Compile scheduler.cpp to scheduler.o
scheduler.o: $(PROCESSHEADERS) $(THREADHEADERS) ProcessScheduling/scheduler.cpp
	$(CLANG) $(CLANGFLAGS) -c  $(GTEST_INC) ProcessScheduling/scheduler.cpp -o scheduler.o

# Compile processschedulingtests.cpp to processschedulingtests.o
processschedulingtests.o: $(PROCESSHEADERS) $(THREADHEADERS) Tests/processschedulingtests.cpp
	$(CLANG) $(CLANGFLAGS) -c  $(GTEST_INC) Tests/processschedulingtests.cpp -o processschedulingtests.o

# compile threadmanagertests.cpp to threadmanagertests.o
threadmanagertests.o: $(PROCESSHEADERS) $(THREADHEADERS) Tests/threadmanagertests.cpp
	$(CLANG) $(CLANGFLAGS) -c  $(GTEST_INC) Tests/threadmanagertests.cpp -o threadmanagertests.o

# Compile threadmanager.cpp to threadmanager.o
threadmanager.o: $(THREADHEADERS) ThreadManager/threadManager.cpp
	$(CLANG) $(CLANGFLAGS) -c  $(GTEST_INC) ThreadManager/threadManager.cpp -o threadmanager.o

# Compile test.cpp to test.o
test.o: Tests/test.cpp
	$(CLANG) $(CLANGFLAGS) -c $(GTEST_INC) Tests/test.cpp -o test.o

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