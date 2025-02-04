#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "ready_queue.hpp"
#include "pcb.hpp"
#include <iostream>

/**
 * @brief A class to manage the scheduling of processes.
 */
class Scheduler
{
public:
    /**
     * @brief Construct a new Scheduler object.
     */
    Scheduler() : currentProcess(nullptr) {}

    /**
     * @brief Add a process to the scheduler.
     *
     * @param pcb Process to add to the ready queue.
     */
    void addProcess(ProcessControlBlock pcb)
    {
        readyQueue.addProcess(pcb);
    }

    /**
     * @brief Schedule the next process based on FCFS.
     */
    void schedule()
    {
        if (currentProcess != nullptr)
        {
            std::cout << "Process " << currentProcess->id << " finished execution." << std::endl;
            delete currentProcess;
            currentProcess = nullptr;
        }

        if (!readyQueue.isEmpty())
        {
            currentProcess = new ProcessControlBlock(readyQueue.getNextProcess());
            if (currentProcess == nullptr)
            {
                std::cerr << "Failed to allocate memory for currentProcess" << std::endl;
                exit(EXIT_FAILURE);
            }

            currentProcess->task(currentProcess->id);
        }
        else
        {
            std::cout << "No more processes to schedule." << std::endl;
        }
    }

    ReadyQueue readyQueue;               // The ready queue of processes
    ProcessControlBlock *currentProcess; // The current process
};

#endif // SCHEDULER_H