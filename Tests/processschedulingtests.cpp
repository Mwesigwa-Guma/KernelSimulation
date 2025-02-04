#include "../ProcessScheduling/scheduler.hpp"
#include <gtest/gtest.h>
#include <iostream>

// Mock function to simulate process execution
void processFunction(int processId) {
    std::cout << "Running Process " << processId << std::endl;
}

// Test fixture for Scheduler tests
class SchedulerTest : public ::testing::Test {
protected:
    Scheduler scheduler;
    ProcessControlBlock *pcb1;
    ProcessControlBlock *pcb2;

    void SetUp() override {
        // Initialize the scheduler with some processes
        pcb1 = new ProcessControlBlock(1, processFunction);
        pcb2 = new ProcessControlBlock(2, processFunction);

        scheduler.addProcess(*pcb1);
        scheduler.addProcess(*pcb2);
    }

    void TearDown() override {
        if (pcb1 != nullptr) {
            delete pcb1;
            pcb1 = nullptr;
        }
        if (pcb2 != nullptr) {
            delete pcb2;
            pcb2 = nullptr;
        }
    }
};

// Test case to check if processes are added to the scheduler
TEST_F(SchedulerTest, AddProcess) {
    ProcessControlBlock *pcb3 = new ProcessControlBlock(3, processFunction);
    scheduler.addProcess(*pcb3);

    // Check if the process was added to the ready queue
    EXPECT_FALSE(scheduler.readyQueue.isEmpty());

    delete pcb3; // Clean up dynamically allocated memory
}

// Test case to check if the scheduler schedules processes correctly
TEST_F(SchedulerTest, ScheduleProcess) {
    scheduler.schedule();

    // Check if the current process is not null after scheduling
    EXPECT_NE(scheduler.currentProcess, nullptr);
}

// Test case to check if the scheduler handles an empty ready queue
TEST_F(SchedulerTest, EmptyReadyQueue) {
    // Clear the ready queue
    while (!scheduler.readyQueue.isEmpty()) {
        scheduler.schedule();
    }

    // Check if the ready queue is empty
    EXPECT_TRUE(scheduler.readyQueue.isEmpty());

    // Check if the scheduler handles an empty ready queue
    scheduler.schedule();
    EXPECT_EQ(scheduler.currentProcess, nullptr);
}