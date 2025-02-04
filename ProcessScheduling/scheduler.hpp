#include "ready_queue.hpp"
#include "pcb.hpp"

/**
 * @brief A class to manage the scheduling of processes.
 * 
 */
class Scheduler
{
public:
    Scheduler() : currentProcess(nullptr) {}

    void addProcess(ProcessControlBlock pcb);
    void schedule();

    ReadyQueue readyQueue;               // The ready queue of processes
    ProcessControlBlock *currentProcess; // The current process
};