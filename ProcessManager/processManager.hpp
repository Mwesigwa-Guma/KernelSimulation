#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "readyQueue.hpp"
#include "pcb.hpp"
#include "../SystemCall/systemCall.hpp"

/**
 * @brief A class to manage the scheduling of processes.
 *
 */
class ProcessManager
{
        void runProcess(ProcessControlBlock *p);
        void createProcess(); // Add this line
        int quantum = 1;           // Time slice for each thread
        int currentProcessId = 0; // The ID of the current process
        int currentStartAddress = 0; // The start address of the current process
        SystemCallTable systemCallTable; // System call table
        
    public:
        ProcessManager() {}
        ~ProcessManager();

        // void addProcess(ProcessControlBlock* pcb, std::function<void()> func); // Remove this line
        void schedule();
        void registerSysCall(SystemCallID id);
        void invokeSysCall(SystemCallID id);
        void sendMessage(int processId, const std::string& message);
        std::string receiveMessage(int processId);

        ReadyQueue readyQueue; // The ready queue of processes
};

#endif // PROCESSMANAGER_H