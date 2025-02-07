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

// Test fixture for process manager tests
class ThreadManagerTest : public ::testing::Test
{
protected:
    ThreadManager manager;

    ThreadManagerTest() : manager() {} // Initialize ThreadManager with quantum of 2

    void SetUp() override
    {
        // create two threads
        manager.createThread(threadOne);
        manager.createThread(threadTwo);
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

// Test case to check if threads are added to the processmanager
TEST_F(ThreadManagerTest, AddThread)
{
    manager.createThread(threadThree);

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

// Test case to check if the process manager schedules processes correctly
TEST_F(ThreadManagerTest, Run)
{
    EXPECT_NO_THROW(manager.runAll());
}