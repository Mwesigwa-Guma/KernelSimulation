# Kernel Simulation Project

This project simulates a simple kernel with process and thread management, memory management, and inter-process communication (IPC). The kernel includes a process manager, thread manager, memory manager, and system call interface.

## Project Structure

- `ProcessManager/`: Contains the process manager and related files.
- `ThreadManager/`: Contains the thread manager and related files.
- `MemoryManager/`: Contains the memory manager and related files.
- `SystemCall/`: Contains the system call interface and related files.
- `Tests/`: Contains the test files for the project.
- `simulate.cpp`: A simulation file that demonstrates two processes passing messages to each other.
- `Makefile`: The makefile to build the project.

## Building the Project

To build the project, run the following command:

```sh
make
```

This will compile the project and create two executables: `test` and `simulate`.

## Running the Simulation

To run the simulation, execute the following command:

```sh
./simulate
```

The simulation demonstrates two processes passing messages to each other.

## Running the Tests

To run the tests, execute the following command:

```sh
./test
```

The tests use Google Test to verify the functionality of the process manager, thread manager, memory manager, and system call interface.

## Project Components

### Process Manager

The process manager is responsible for creating, scheduling, and managing processes. It uses a round-robin scheduling algorithm and supports inter-process communication (IPC) through message passing.

### Thread Manager

The thread manager is responsible for creating and managing threads within a process. It uses a ready queue to manage the execution of threads.

### Memory Manager

The memory manager is responsible for allocating and deallocating memory for processes. It uses a memory map to track allocated and free memory blocks.

### System Call Interface

The system call interface provides a way for processes to request services from the kernel. It supports system calls for creating processes and allocating memory.
