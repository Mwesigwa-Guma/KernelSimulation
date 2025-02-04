#ifndef PCB_H
#define PCB_H

#include <iostream>

/**
 * @brief A struct to represent a process control block.
 */
struct ProcessControlBlock {
    int id;                // Process ID
    void (*task)(int);     // Function to execute for this process

    /**
     * @brief Construct a new ProcessControlBlock object.
     *
     * @param processId The ID of the process.
     * @param func Pointer to the function to execute in this process.
     */
    ProcessControlBlock(int processId, void (*func)(int))
        : id(processId), task(func) {}

    /**
     * @brief Destroy the ProcessControlBlock object.
     */
    ~ProcessControlBlock() {}
};

#endif // PCB_H