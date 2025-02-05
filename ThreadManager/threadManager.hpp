#pragma once

#include <iostream>
#include <functional>
#include <csetjmp>
#include "threadReadyQueue.hpp"

// Thread Control Block (TCB)
struct ThreadControlBlock {
    std::function<void()> task;
};

class ThreadManager {
public:
    void createThread(std::function<void()> func);
    void run();

    ThreadReadyQueue threadReadyQueue;
};