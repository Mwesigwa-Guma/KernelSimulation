#include "ready_queue.hpp"
#include "pcb.hpp"

/**
 * @brief A class to manage the scheduling of processes.
 *
 */
class Scheduler
{
        void runProcess(ProcessControlBlock *p);
        int quantum = 1;           // Time slice for each process
    public:
        Scheduler() {}
        ~Scheduler();

        void addProcess(ProcessControlBlock* pcb, std::function<void()> func);
        void schedule();
        void sendMessage(int processId, const std::string& message);
        std::string receiveMessage(int processId);

        ReadyQueue readyQueue; // The ready queue of processes
};