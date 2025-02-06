#include "ready_queue.hpp"
#include "pcb.hpp"
#include "../SystemCall/system_call.hpp"

/**
 * @brief A class to manage the scheduling of processes.
 *
 */
class Scheduler
{
        void runProcess(ProcessControlBlock *p);
        int quantum = 1;           // Time slice for each thread
    public:
        Scheduler() {}
        ~Scheduler();

        // void addProcess(ProcessControlBlock* pcb, std::function<void()> func); // Remove this line
        void schedule();
        void createProcess(std::function<void()> func); // Add this line
        void sendMessage(int processId, const std::string& message);
        std::string receiveMessage(int processId);

        ReadyQueue readyQueue; // The ready queue of processes
        SystemCallTable systemCallTable; // System call table
        int currentProcessId = 0; // The ID of the current process
};