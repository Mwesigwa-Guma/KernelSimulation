
#include "threadManager.hpp"

void ThreadManager::createThread(int remainingTime, std::function<void()> func)
{
    ThreadControlBlock *tcb = new ThreadControlBlock();
    tcb->state = ThreadState::READY;
    tcb->task = func;
    tcb->remaining_time = remainingTime;
    threads.push(tcb);
}

void ThreadManager::run()
{
    while (true) {
        int all_done = 1;
        while (!threads.empty()) {
            ThreadControlBlock* thread = threads.front();
            threads.pop();
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
            t->task(); // Execute the thread's task
            t->remaining_time -= quantum;
        } else {
            t->remaining_time = 0; // Process completed
        }
        // If process not finished, reschedule
        if (t->remaining_time > 0) {
            threads.push(t);
            longjmp(t->context, 1);
        }else {
            std::cout << "Thread completed" << std::endl;
            delete t; // Clean up completed process
        }
    }
}