# Compiler
CLANG = clang++

# Compiler flags
CLANGFLAGS = -g -Wall -std=c++17

# Include path for Google Test PROCESSHEADERS
GTEST_INC = -I/opt/homebrew/include

# Library path and linking flags for Google Test
GTEST_LIB = -L/opt/homebrew/lib -lgtest -lgtest_main -pthread

# header files
PROCESSHEADERS = ProcessManager/processManager.hpp ProcessManager/ready_queue.hpp ProcessManager/pcb.hpp ProcessManager/message_queue.hpp

# thread headers
THREADHEADERS = ThreadManager/ThreadManager.hpp ThreadManager/threadReadyQueue.hpp

# system call headers
SYSCALLHEADERS = SystemCall/system_call.hpp

# Object files
OBJS = test.o processManager.o ProcessManagertests.o threadmanager.o threadmanagertests.o system_call.o memorymanager.o

# Executable name
EXEC = simulate

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CLANG) $(CLANGFLAGS) $(GTEST_LIB) -o $(EXEC) $(OBJS)

# Compile processManager.cpp to processManager.o
processManager.o: ProcessManager/processManager.cpp
	$(CLANG) $(CLANGFLAGS) -c  $(GTEST_INC) ProcessManager/processManager.cpp -o processManager.o

# Compile ProcessManagertests.cpp to ProcessManagertests.o
ProcessManagertests.o: Tests/ProcessManagertests.cpp
	$(CLANG) $(CLANGFLAGS) -c  $(GTEST_INC) Tests/ProcessManagertests.cpp -o ProcessManagertests.o

# compile threadmanagertests.cpp to threadmanagertests.o
threadmanagertests.o: Tests/threadmanagertests.cpp
	$(CLANG) $(CLANGFLAGS) -c  $(GTEST_INC) Tests/threadmanagertests.cpp -o threadmanagertests.o

# Compile threadmanager.cpp to threadmanager.o
threadmanager.o: ThreadManager/threadManager.cpp
	$(CLANG) $(CLANGFLAGS) -c  $(GTEST_INC) ThreadManager/threadManager.cpp -o threadmanager.o

# Compile system_call.cpp to system_call.o
system_call.o: SystemCall/system_call.cpp
	$(CLANG) $(CLANGFLAGS) -c  $(GTEST_INC) SystemCall/system_call.cpp -o system_call.o

# comile memorymanager.cpp to memorymanager.o
memorymanager.o: MemoryManager/memoryManager.cpp
	$(CLANG) $(CLANGFLAGS) -c  $(GTEST_INC) MemoryManager/memoryManager.cpp -o memorymanager.o

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