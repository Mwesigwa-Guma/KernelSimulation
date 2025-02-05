
#include "threadManager.hpp"

void ThreadManager::createThread(int remainingTime, std::function<void()> func)
{
    ThreadControlBlock *tcb = new ThreadControlBlock();
    tcb->state = ThreadState::READY;
    tcb->task = func;
    tcb->remaining_time = remainingTime;
    threadReadyQueue.addThread(tcb);
}

void ThreadManager::run()
{
    while (true) {
        int all_done = 1;
        while (!threadReadyQueue.isEmpty()) {
            ThreadControlBlock* thread = threadReadyQueue.getNextThread();
            if (thread->remaining_time > 0) {
                all_done = 0;
                runThread(thread);
            }
        }
        if (all_done) {
            break; 
        }
    }
}

void ThreadManager::runThread(ThreadControlBlock *t) {
    if (setjmp(t->context) == 0) {
        // Execute thread for one quantum
        if (t->remaining_time > quantum) {
            t->state = ThreadState::RUNNING; // Set state to RUNNING
            t->task(); // Execute the thread's task
            t->remaining_time -= quantum;
        } else {
            t->remaining_time = 0; // Process completed
        }
        // If process not finished, reschedule
        if (t->remaining_time > 0) {
            t->state = ThreadState::READY; // Set state to READY
            threadReadyQueue.addThread(t);
            longjmp(t->context, 1);
        }else {
            t->state = ThreadState::TERMINATED; // Set state to TERMINATED
            delete t; // Clean up completed process
        }
    }
}