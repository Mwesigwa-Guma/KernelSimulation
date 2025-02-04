#include "scheduler.hpp"
#include <iostream>

/**
 * @brief Add a process to the scheduler.
 *
 * @param pcb Process to add to the ready queue.
 */
void Scheduler::addProcess(ProcessControlBlock pcb)
{
    readyQueue.addProcess(pcb);
}

/**
 * @brief Schedule the next process based on FCFS.
 */
void Scheduler::schedule()
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
