#include "ProcessManager/processManager.hpp"
#include "SystemCall/systemCall.hpp"
#include <iostream>

void process1Func(ProcessManager& processManager) {
    processManager.sendMessage(2, "Hello from Process 1");
    std::string message = processManager.receiveMessage(1);
    std::cout << "Process 1 received: " << message << std::endl;
}

void process2Func(ProcessManager& processManager) {
    std::string message = processManager.receiveMessage(2);
    std::cout << "Process 2 received: " << message << std::endl;
    processManager.sendMessage(1, "Hello from Process 2");
}

int main() {
    ProcessManager processManager;

    // Register system calls
    processManager.registerSysCall(SystemCallID::CREATE_PROCESS);

    // Create two processes
    processManager.invokeSysCall(SystemCallID::CREATE_PROCESS);
    processManager.invokeSysCall(SystemCallID::CREATE_PROCESS);

    // Assign functions to processes
    processManager.readyQueue.getNextProcess()->threadManager.createThread([&processManager]() { process1Func(processManager); });
    processManager.readyQueue.getNextProcess()->threadManager.createThread([&processManager]() { process2Func(processManager); });

    // Schedule processes
    processManager.schedule();

    return 0;
}
