#ifndef PCB_H
#define PCB_H

#include <iostream>
#include <setjmp.h>

/**
 * @brief A struct to represent a process control block.
 */
struct ProcessControlBlock {
    int id;
    int remaining_time;               
    jmp_buf context;       // Context for setjmp/longjmp
    

    /**
     * @brief Construct a new ProcessControlBlock object.
     *
     * @param processId The ID of the process.
     * @param func Pointer to the function to execute in this process.
     */
    ProcessControlBlock(int processId, int remainingTime)
        : id(processId), remaining_time(remainingTime) {}

    /**
     * @brief Destroy the ProcessControlBlock object.
     */ 
    ~ProcessControlBlock() {}
};

#endif // PCB_H