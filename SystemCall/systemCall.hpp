#ifndef SYSTEMCALL_H
#define SYSTEMCALL_H

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
    void registerSystemCall(SystemCallID id, SystemCallFunction func);
    void invokeSystemCall(SystemCallID id);
    
private:
    std::unordered_map<SystemCallID, SystemCallFunction> table;
};


void create_process();
void allocate_memory();

#endif // SYSTEMCALL_H
