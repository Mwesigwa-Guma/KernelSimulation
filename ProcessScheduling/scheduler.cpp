#include "scheduler.hpp"
#include <iostream>

/**
 * @brief Add a process to the scheduler.
 *
 * @param pcb Process to add to the ready queue.
 */
void Scheduler::addProcess(ProcessControlBlock* pcb)
{
    readyQueue.addProcess(pcb);
}

/**
 * @brief Schedule the next process based on round-robin.
 */
void Scheduler::schedule() {
    while (true) {
        int all_done = 1;
        while (!readyQueue.isEmpty()) {
            ProcessControlBlock* process = readyQueue.getNextProcess();
            if (process->remaining_time > 0) {
                all_done = 0;
                std::cout << "Executing process " << process->id << std::endl;
                runProcess(process);
            }
        }
        if (all_done) {
            break; 
        }
    }
}

void Scheduler::runProcess(ProcessControlBlock *p) {
    if (setjmp(p->context) == 0) {
        // Execute process for one quantum
        if (p->remaining_time > quantum) {
            p->remaining_time -= quantum;
        } else {
            p->remaining_time = 0; // Process completed
        }
        // If process not finished, reschedule
        if (p->remaining_time > 0) {
            readyQueue.addProcess(p);
            longjmp(p->context, 1);
        }else {
            std::cout << "Process completed : " << p->id << std::endl;
            delete p; // Clean up completed process
        }
    }
}

/**
 * @brief Send a message to a process.
 *
 * @param processId The ID of the process to send the message to.
 * @param message The message to send.
 */
void Scheduler::sendMessage(int processId, const std::string& message) {
    // Find the process with the given ID and send the message
    std::queue<ProcessControlBlock*> tempQueue;
    while (!readyQueue.isEmpty()) {
        ProcessControlBlock* process = readyQueue.getNextProcess();
        if (process->id == processId) {
            process->msgQueue.send(message);
        }
        tempQueue.push(process);
    }
    // Restore the ready queue
    while (!tempQueue.empty()) {
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
std::string Scheduler::receiveMessage(int processId) {
    // Find the process with the given ID and receive the message
    std::queue<ProcessControlBlock*> tempQueue;
    std::string message;
    while (!readyQueue.isEmpty()) {
        ProcessControlBlock* process = readyQueue.getNextProcess();
        if (process->id == processId) {
            message = process->msgQueue.receive();
        }
        tempQueue.push(process);
    }
    // Restore the ready queue
    while (!tempQueue.empty()) {
        readyQueue.addProcess(tempQueue.front());
        tempQueue.pop();
    }
    return message;
}