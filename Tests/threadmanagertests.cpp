#include "../ThreadManager/threadManager.hpp"
#include <gtest/gtest.h>
#include <iostream>

void threadOne()
{
    std::cout << "Thread 1 running" << std::endl;
}

void threadTwo()
{
    std::cout << "Thread 2 running" << std::endl;
}

void threadThree()
{
    std::cout << "Thread 3 running" << std::endl;
}

// Test fixture for Scheduler tests
class ThreadManagerTest : public ::testing::Test
{
protected:
    ThreadManager manager;

    ThreadManagerTest() : manager(2) {} // Initialize ThreadManager with quantum of 2

    void SetUp() override
    {
        // create two threads
        manager.createThread(3, threadOne);
        manager.createThread(5, threadTwo);
    }

    void TearDown() override
    {
        std::cout << "TearDown created resources" << std::endl;
        while (!manager.threadReadyQueue.isEmpty())
        {
            ThreadControlBlock *t = manager.threadReadyQueue.getNextThread();
            delete t;
        }
    }
};

// Test case to check if threads are added to the scheduler
TEST_F(ThreadManagerTest, AddThread)
{
    manager.createThread(2, threadThree);

    // Check if the process was added to the ready queue
    EXPECT_FALSE(manager.threadReadyQueue.isEmpty());
}

// Test case to run thread tasks
TEST_F(ThreadManagerTest, RunThreadTasks)
{
    ThreadControlBlock *t1 = manager.threadReadyQueue.getNextThread();
    EXPECT_NO_THROW(t1->task());

    ThreadControlBlock *t2 = manager.threadReadyQueue.getNextThread();
    EXPECT_NO_THROW(t1->task());

    EXPECT_TRUE(manager.threadReadyQueue.isEmpty());
    // delete threads
    delete t1;
    delete t2;
}

// Test case to check if the scheduler schedules processes correctly
TEST_F(ThreadManagerTest, Run)
{
    EXPECT_NO_THROW(manager.run());
}