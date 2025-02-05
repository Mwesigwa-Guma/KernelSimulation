#include "threadManager.hpp"

// implement destructor for ThreadManager
ThreadManager::~ThreadManager() {
    while (!threadReadyQueue.isEmpty()) {
        ThreadControlBlock* t = threadReadyQueue.getNextThread();
        delete t;
    }
}

void ThreadManager::createThread(std::function<void()> func)
{
    ThreadControlBlock *tcb = new ThreadControlBlock();
    tcb->task = func;
    threadReadyQueue.addThread(tcb);
}

void ThreadManager::runAll()
{
    while (!threadReadyQueue.isEmpty()) {
        ThreadControlBlock* thread = threadReadyQueue.getNextThread();
        thread->task();
    }
}

// run next thread in queue
void ThreadManager::runNext(){
    if (!threadReadyQueue.isEmpty()) {
        ThreadControlBlock* thread = threadReadyQueue.getNextThread();
        thread->task();
    }
}
