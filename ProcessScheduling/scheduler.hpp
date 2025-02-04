#include "ready_queue.hpp"
#include "pcb.hpp"

/**
 * @brief A class to manage the scheduling of processes.
 *
 */
class Scheduler
{
        void runProcess(ProcessControlBlock *p);

    public:
        Scheduler(int quantum) : quantum(quantum) {}

        void addProcess(ProcessControlBlock pcb);
        void schedule();

        ReadyQueue readyQueue; // The ready queue of processes
        int quantum;           // Time slice for each process
};