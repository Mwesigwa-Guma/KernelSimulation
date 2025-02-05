#pragma once

#include <iostream>
#include <functional>
#include <csetjmp>
#include "threadReadyQueue.hpp"

// Thread State Enum
enum class ThreadState { READY, RUNNING, TERMINATED };

// Thread Control Block (TCB)
struct ThreadControlBlock {
    std::jmp_buf context;
    ThreadState state;
    int remaining_time;
    std::function<void()> task;
};

class ThreadManager {
private:
    void runThread(ThreadControlBlock *p);
public:
    ThreadManager(int quant) : quantum(quant){}
    void createThread(int remainingTime, std::function<void()> func);
    void run();

    ThreadReadyQueue threadReadyQueue;
    int quantum;
};