// filepath: /Users/mwesigwaguma/Desktop/repos/Projects/KernelSimulation/readyQueue.h
#ifndef READYQUEUE_H
#define READYQUEUE_H

#include "pcb.hpp"
#include <queue>

/**
 * @brief A class to manage the ready queue of processes.
 */
class ReadyQueue
{
public:
    /**
     * @brief Add a process to the ready queue.
     *
     * @param pcb Process to add to the ready queue.
     */
    void addProcess(ProcessControlBlock* pcb)
    {
        queue.push(pcb);
    }

    /**
     * @brief Get the next process based on FCFS.
     *
     * @return ProcessControlBlock* The next process to be scheduled.
     */
    ProcessControlBlock* getNextProcess()
    {
        if (queue.empty())
        {
            throw std::runtime_error("Ready queue is empty.");
        }
        ProcessControlBlock* pcb = queue.front();
        queue.pop();
        return pcb;
    }

    /**
     * @brief Check if the ready queue is empty.
     *
     * @return true if the ready queue is empty, false otherwise.
     */
    bool isEmpty() const
    {
        return queue.empty();
    }

private:
    /**
     * @brief The ready queue of processes.
     */
    std::queue<ProcessControlBlock*> queue;
};

#endif // READYQUEUE_H