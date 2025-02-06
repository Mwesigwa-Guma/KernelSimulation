
/*This file is not being used but maybe usefull later*/

#include "system_call.hpp"
#include "../ProcessScheduling/pcb.hpp"
#include "../ProcessScheduling/scheduler.hpp"
#include "../ThreadManager/threadManager.hpp"
#include <iostream>



// Simulated system call to create a process
void create_process(int id, int remaining_time, Scheduler scheduler) {
    // Create a new process
}

// Simulated system call to allocate memory
void allocate_memory() {
    std::cout << "Simulated system call: allocate_memory" << std::endl;
    // Implement memory allocation logic here
}