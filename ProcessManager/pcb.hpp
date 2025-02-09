#ifndef PCB_H
#define PCB_H

#include <iostream>
#include <setjmp.h>
#include "messageQueue.hpp"
#include "../ThreadManager/threadManager.hpp"

/**
 * @brief A struct to represent a process control block.
 */
struct ProcessControlBlock {
    int id;
    int remaining_time;               
    jmp_buf context;       // Context for setjmp/longjmp
    MessageQueue msgQueue; // Message queue for IPC
    ThreadManager threadManager; // Thread manager for executing thread tasks

    /**
     * @brief Construct a new ProcessControlBlock object.
     *
     * @param processId The ID of the process.
     * @param remainingTime The remaining time for the process.
     */
    ProcessControlBlock(int processId, int remainingTime)
        : id(processId), remaining_time(remainingTime) {}

    /**
     * @brief Destroy the ProcessControlBlock object.
     */ 
    ~ProcessControlBlock() {}
};

#endif // PCB_H