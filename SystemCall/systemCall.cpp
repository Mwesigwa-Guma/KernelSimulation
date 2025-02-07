
/*This file is not being used but maybe usefull later*/

#include "systemCall.hpp"
#include <iostream>

void SystemCallTable::registerSystemCall(SystemCallID id, SystemCallFunction func)
{
    table[id] = func;
}

void SystemCallTable::invokeSystemCall(SystemCallID id)
{
    if (table.find(id) != table.end())
    {
        table[id]();
    }
    else
    {
        throw std::runtime_error("System call with id()not found.");
    }
}

// Simulated system call to create a process
void SystemCallTable::create_process(std::function<void()> threadFunc)
{
    processManager.createProcess(threadFunc);
}

// Simulated system call to allocate memory
void SystemCallTable::allocate_memory()
{
    std::cout << "Simulated system call: allocate_memory" << std::endl;
    // Implement memory allocation logic here
}