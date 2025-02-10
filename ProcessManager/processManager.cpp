#include "processManager.hpp"
#include <iostream>

// implement destructor for process manager
ProcessManager::~ProcessManager()
{
    while (!readyQueue.isEmpty())
    {
        ProcessControlBlock *p = readyQueue.getNextProcess();
        delete p;
        p = nullptr;
    }
}

/**
 * @brief Add a process to the process manger.
 *
 * @param pcb Process to add to the ready queue.
 */
void ProcessManager::createProcess()
{
    ProcessControlBlock *pcb = new ProcessControlBlock(++currentProcessId, 1);
    currentStartAddress = pcb->memoryMap.allocateMemory(currentStartAddress+10);
    for (int i = 0; i < pcb->remaining_time; i += quantum)
    {
        pcb->threadManager.createThread([pcb]()
                                        { pcb->memoryMap.displayMemoryMap(); });
    }

    readyQueue.addProcess(pcb);
}

void ProcessManager::registerSysCall(SystemCallID id)
{
    if (id == SystemCallID::CREATE_PROCESS)
    {
        systemCallTable.registerSystemCall(id, [this]()
                                           { createProcess(); });
    }
    else
    {
        throw std::runtime_error("System call not found");
    }
}

void ProcessManager::invokeSysCall(SystemCallID id)
{
    if (id == SystemCallID::CREATE_PROCESS)
    {
        systemCallTable.invokeSystemCall(id);
    }
    else
    {
        throw std::runtime_error("System call not found");
    }
}

/**
 * @brief Schedule the next process based on round-robin.
 */
void ProcessManager::schedule()
{
    while (true)
    {
        int all_done = 1;
        while (!readyQueue.isEmpty())
        {
            ProcessControlBlock *process = readyQueue.getNextProcess();
            if (process->remaining_time > 0)
            {
                all_done = 0;
                std::cout << "Executing process " << process->id << std::endl;
                runProcess(process);
            }
        }
        if (all_done)
        {
            break;
        }
    }
}

void ProcessManager::runProcess(ProcessControlBlock *p)
{
    if (setjmp(p->context) == 0)
    {
        // Execute process for one quantum
        if (p->remaining_time > quantum)
        {
            // Execute thread tasks using ThreadManager within the process
            p->threadManager.runNext();
            p->remaining_time -= quantum;
        }
        else
        {
            p->threadManager.runNext(); // Execute remaining time
            p->remaining_time = 0;      // Process completed
        }
        // If process not finished, reschedule
        if (p->remaining_time > 0)
        {
            readyQueue.addProcess(p);
            longjmp(p->context, 1);
        }
        else
        {
            std::cout << "Process completed : " << p->id << std::endl;
            p->memoryMap.deallocateMemory(0);
            delete p;    // Clean up completed process
            p = nullptr; // Set pointer to nullptr to avoid dangling pointer
        }
    }
}

/**
 * @brief Send a message to a process.
 *
 * @param processId The ID of the process to send the message to.
 * @param message The message to send.
 */
void ProcessManager::sendMessage(int processId, const std::string &message)
{
    // Find the process with the given ID and send the message
    std::queue<ProcessControlBlock *> tempQueue;
    while (!readyQueue.isEmpty())
    {
        ProcessControlBlock *process = readyQueue.getNextProcess();
        if (process->id == processId)
        {
            process->msgQueue.send(message);
        }
        tempQueue.push(process);
    }
    // Restore the ready queue
    while (!tempQueue.empty())
    {
        readyQueue.addProcess(tempQueue.front());
        tempQueue.pop();
    }
}

/**
 * @brief Receive a message from a process.
 *
 * @param processId The ID of the process to receive the message from.
 * @return std::string The received message.
 */
std::string ProcessManager::receiveMessage(int processId)
{
    // Find the process with the given ID and receive the message
    std::queue<ProcessControlBlock *> tempQueue;
    std::string message;
    while (!readyQueue.isEmpty())
    {
        ProcessControlBlock *process = readyQueue.getNextProcess();
        if (process->id == processId)
        {
            message = process->msgQueue.receive();
        }
        tempQueue.push(process);
    }
    // Restore the ready queue
    while (!tempQueue.empty())
    {
        readyQueue.addProcess(tempQueue.front());
        tempQueue.pop();
    }
    return message;
}