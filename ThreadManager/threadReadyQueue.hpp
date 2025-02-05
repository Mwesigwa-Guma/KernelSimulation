#ifndef THREADREADYQUEUE_H
#define THREADREADYQUEUE_H

#include <queue>
#include <stdexcept>

// Forward declaration of ThreadControlBlock
struct ThreadControlBlock;

// Ready Queue
class ThreadReadyQueue {
    std::queue<ThreadControlBlock*> threads;
public:
    void addThread(ThreadControlBlock* t){
        threads.push(t);
    }

    ThreadControlBlock* getNextThread(){
        if (threads.empty()) {
            throw std::runtime_error("thread queue is empty");
        }

        ThreadControlBlock* t = threads.front();
        threads.pop();
        return t;
    }

    bool isEmpty() const {
        return threads.empty();
    }
};

#endif // THREADREADYQUEUE_H