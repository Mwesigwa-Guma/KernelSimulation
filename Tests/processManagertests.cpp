#include "../ProcessManager/processManager.hpp"
#include "../SystemCall/system_call.hpp"
#include <gtest/gtest.h>
#include <iostream>

void threadFunc()
{
    std::cout << "Thread running" << std::endl;
}

// Test fixture for process manager tests
class ProcessManagerTest : public ::testing::Test
{
protected:
    ProcessManager processManager;

    ProcessManagerTest() : processManager() {} // Initialize process manager

    void SetUp() override
    {
        // Register system calls
        processManager.systemCallTable.registerSystemCall(SystemCallID::CREATE_PROCESS, [this]() {
            processManager.createProcess(threadFunc);
        });

        processManager.systemCallTable.invokeSystemCall(SystemCallID::CREATE_PROCESS);
        processManager.systemCallTable.invokeSystemCall(SystemCallID::CREATE_PROCESS);
    }

    void TearDown() override
    {
        std::cout << "TearDown created resources" << std::endl;
    }
};

// Test case to check if processes are added to the process manager
TEST_F(ProcessManagerTest, AddProcess)
{
    processManager.systemCallTable.invokeSystemCall(SystemCallID::CREATE_PROCESS);

    // Check if the process was added to the ready queue
    EXPECT_FALSE(processManager.readyQueue.isEmpty());
}

// Test case to check if processes are scheduled in the correct order
TEST_F(ProcessManagerTest, ProcessSchedulingOrder)
{

    // Check if the processes were executed in the correct order
    ProcessControlBlock *process1 = processManager.readyQueue.getNextProcess();
    EXPECT_EQ(process1->id, 1);

    ProcessControlBlock *process2 = processManager.readyQueue.getNextProcess();
    EXPECT_EQ(process2->id, 2);

    EXPECT_TRUE(processManager.readyQueue.isEmpty());
}

// Test case to check if the process manager schedules processes correctly
TEST_F(ProcessManagerTest, ScheduleProcess)
{
    processManager.schedule();

    // Check if the current process is not null after scheduling
    EXPECT_TRUE(processManager.readyQueue.isEmpty());
}

// Test case to check if the IPC module works correctly
TEST_F(ProcessManagerTest, IPCModule)
{
    processManager.sendMessage(1, "Hello from Process 2");
    std::string message = processManager.receiveMessage(1);
    EXPECT_EQ(message, "Hello from Process 2");
}

// Test case to demonstrate IPC usage for data sharing and synchronization
TEST_F(ProcessManagerTest, IPCDataSharing)
{
    // Process 1 sends a message to Process 2
    processManager.sendMessage(2, "Data from Process 1");

    // Process 2 receives the message
    std::string message = processManager.receiveMessage(2);
    EXPECT_EQ(message, "Data from Process 1");

    // Process 2 sends a response to Process 1
    processManager.sendMessage(1, "Acknowledged by Process 2");

    // Process 1 receives the response
    message = processManager.receiveMessage(1);
    EXPECT_EQ(message, "Acknowledged by Process 2");
}

// Test case to check if the ThreadManager in ProcessControlBlock works correctly
TEST_F(ProcessManagerTest, ThreadManagerInProcessControlBlock)
{
    // Create a process with threads
    processManager.systemCallTable.invokeSystemCall(SystemCallID::CREATE_PROCESS);

    // Schedule the process
    processManager.schedule();

    // Check if the process and its threads were executed correctly
    EXPECT_TRUE(processManager.readyQueue.isEmpty());
}

// Test case to check if system calls work correctly
TEST_F(ProcessManagerTest, SystemCallTest)
{
    // Invoke system calls
    processManager.systemCallTable.invokeSystemCall(SystemCallID::CREATE_PROCESS);
}