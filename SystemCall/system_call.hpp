#ifndef SYSTEM_CALL_H
#define SYSTEM_CALL_H

#include <unordered_map>
#include <functional>
#include <string>

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

    int processIdCounter = 0;
    void registerSystemCall(SystemCallID id, SystemCallFunction func) {
        table[id] = func;
    }

    void invokeSystemCall(SystemCallID id) {
        if (table.find(id) != table.end()) {
            table[id]();
        } else {
            throw std::runtime_error("System call with id()not found.");
        }
    }

private:
    std::unordered_map<SystemCallID, SystemCallFunction> table;
};

// Simulated system calls
void create_process();
void allocate_memory();

#endif // SYSTEM_CALL_H
