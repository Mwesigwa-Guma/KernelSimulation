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
            readyQueue.addProcess(*p);
            longjmp(p->context, 1);
        }else {
            std::cout << "Process completed : " << p->id << std::endl;
            delete p; // Clean up completed process
        }
    }
}