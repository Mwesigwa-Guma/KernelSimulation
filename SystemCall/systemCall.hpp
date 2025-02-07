#ifndef SYSTEMCALL_H
#define SYSTEMCALL_H

#include <unordered_map>
#include <functional>
#include <string>
#include "../ProcessManager/processManager.hpp"

// Define system call IDs
enum class SystemCallID {
    CREATE_PROCESS,
    ALLOCATE_MEMORY,
    // Add more system call IDs as needed
};

// Define a type for system call functions
using SystemCallFunction = std::function<void()>;

// System Call Table
class SystemCallTable {
public:
    void registerSystemCall(SystemCallID id, SystemCallFunction func);
    void invokeSystemCall(SystemCallID id);
    void create_process(std::function<void()> threadFunc);
    void allocate_memory();

    ProcessManager processManager;

private:
    std::unordered_map<SystemCallID, SystemCallFunction> table;
};

#endif // SYSTEMCALL_H
