#include "../ProcessScheduling/scheduler.hpp"
#include <gtest/gtest.h>
#include <iostream>

// Test fixture for Scheduler tests
class SchedulerTest : public ::testing::Test
{
protected:
    Scheduler scheduler;
    ProcessControlBlock *pcb1;
    ProcessControlBlock *pcb2;

    SchedulerTest() : scheduler() {} // Initialize scheduler with quantum of 2

    void SetUp() override
    {
        // Initialize the scheduler with some processes
        pcb1 = new ProcessControlBlock(1, 2);
        pcb2 = new ProcessControlBlock(2, 3);

        scheduler.addProcess(pcb1, []() {
            std::cout << "Process 1 running" << std::endl;
        });
        scheduler.addProcess(pcb2, []() {
            std::cout << "Process 2 running" << std::endl;
        });
    }

    void TearDown() override
    {
        std::cout << "TearDown created resources" << std::endl;
    }
};

// Test case to check if processes are added to the scheduler
TEST_F(SchedulerTest, AddProcess)
{
    ProcessControlBlock *pcb3 = new ProcessControlBlock(3, 2);
    scheduler.addProcess(pcb3, []() {
        std::cout << "Process 3 running" << std::endl;
    });

    // Check if the process was added to the ready queue
    EXPECT_FALSE(scheduler.readyQueue.isEmpty());
}

// Test case to check if processes are scheduled in the correct order
TEST_F(SchedulerTest, ProcessSchedulingOrder)
{

    // Check if the processes were executed in the correct order
    ProcessControlBlock *process1 = scheduler.readyQueue.getNextProcess();
    EXPECT_EQ(process1->id, 1);

    ProcessControlBlock *process2 = scheduler.readyQueue.getNextProcess();
    EXPECT_EQ(process2->id, 2);

    EXPECT_TRUE(scheduler.readyQueue.isEmpty());
}

// Test case to check if the scheduler schedules processes correctly
TEST_F(SchedulerTest, ScheduleProcess)
{
    scheduler.schedule();

    // Check if the current process is not null after scheduling
    EXPECT_TRUE(scheduler.readyQueue.isEmpty());
}

// Test case to check if the IPC module works correctly
TEST_F(SchedulerTest, IPCModule)
{
    scheduler.sendMessage(1, "Hello from Process 2");
    std::string message = scheduler.receiveMessage(1);
    EXPECT_EQ(message, "Hello from Process 2");
}

// Test case to demonstrate IPC usage for data sharing and synchronization
TEST_F(SchedulerTest, IPCDataSharing)
{
    // Process 1 sends a message to Process 2
    scheduler.sendMessage(2, "Data from Process 1");

    // Process 2 receives the message
    std::string message = scheduler.receiveMessage(2);
    EXPECT_EQ(message, "Data from Process 1");

    // Process 2 sends a response to Process 1
    scheduler.sendMessage(1, "Acknowledged by Process 2");

    // Process 1 receives the response
    message = scheduler.receiveMessage(1);
    EXPECT_EQ(message, "Acknowledged by Process 2");
}

// Test case to check if the ThreadManager in ProcessControlBlock works correctly
TEST_F(SchedulerTest, ThreadManagerInProcessControlBlock)
{
    // Create a process with threads
    ProcessControlBlock *pcb3 = new ProcessControlBlock(3, 4);
    pcb3->threadManager.createThread([]() {
        std::cout << "Thread 1 in Process 3" << std::endl;
    });
    pcb3->threadManager.createThread([]() {
        std::cout << "Thread 2 in Process 3" << std::endl;
    });

    scheduler.addProcess(pcb3, []() {
        std::cout << "Process 3 running" << std::endl;
    });

    // Schedule the process
    scheduler.schedule();

    // Check if the process and its threads were executed correctly
    EXPECT_TRUE(scheduler.readyQueue.isEmpty());
}