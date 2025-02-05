#include "../ProcessScheduling/scheduler.hpp"
#include <gtest/gtest.h>
#include <iostream>

// Test fixture for Scheduler tests
class SchedulerTest : public ::testing::Test {
protected:
    Scheduler scheduler;
    ProcessControlBlock *pcb1;
    ProcessControlBlock *pcb2;

    SchedulerTest() : scheduler(2) {} // Initialize scheduler with quantum of 2

    void SetUp() override {
        // Initialize the scheduler with some processes
        pcb1 = new ProcessControlBlock(1, 3);
        pcb2 = new ProcessControlBlock(2, 5);

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
    ProcessControlBlock *pcb3 = new ProcessControlBlock(3, 2);
    scheduler.addProcess(*pcb3);

    // Check if the process was added to the ready queue
    EXPECT_FALSE(scheduler.readyQueue.isEmpty());

    delete pcb3; // Clean up dynamically allocated memory
}

// Test case to check if processes are scheduled in the correct order
TEST_F(SchedulerTest, ScheduleProcesses) {

    // Check if the processes were executed in the correct order
    ProcessControlBlock *process1 = scheduler.readyQueue.getNextProcess();
    EXPECT_EQ(process1->id, 1);

    ProcessControlBlock *process2 = scheduler.readyQueue.getNextProcess();
    EXPECT_EQ(process2->id, 2);

    EXPECT_TRUE(scheduler.readyQueue.isEmpty());

    delete process1; // Clean up dynamically allocated memory
    delete process2; // Clean up dynamically allocated memory
}

// Test case to check if the scheduler schedules processes correctly
TEST_F(SchedulerTest, ScheduleProcess) {
    scheduler.schedule();

    // Check if the current process is not null after scheduling
    EXPECT_TRUE(scheduler.readyQueue.isEmpty());
}