
#include "threadManager.hpp"

void ThreadManager::createThread(std::function<void()> func)
{
    ThreadControlBlock *tcb = new ThreadControlBlock();
    tcb->task = func;
    threadReadyQueue.addThread(tcb);
}

void ThreadManager::run()
{
    while (!threadReadyQueue.isEmpty()) {
            ThreadControlBlock* thread = threadReadyQueue.getNextThread();
            thread->task();
            delete thread; // Clean up completed thread
        }
}