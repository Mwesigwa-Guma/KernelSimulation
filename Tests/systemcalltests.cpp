#include "../SystemCall/systemCall.hpp"
#include <gtest/gtest.h>
#include <iostream>

void threadFunc()
{
    std::cout << "Thread running" << std::endl;
}

// Test fixture for System Call tests
class SystemCallTest : public ::testing::Test
{
protected:
    SystemCallTable systemCallTable;

    SystemCallTest() : systemCallTable() {}

    void SetUp() override
    {
        // Register system calls
        systemCallTable.registerSystemCall(SystemCallID::CREATE_PROCESS, create_process);

        systemCallTable.registerSystemCall(SystemCallID::ALLOCATE_MEMORY, allocate_memory);
    }

    void TearDown() override
    {
        std::cout << "TearDown created resources" << std::endl;
    }
};

// Test case to check if system calls work correctly
TEST_F(SystemCallTest, CreateProcessSystemCall)
{
    EXPECT_NO_THROW(systemCallTable.invokeSystemCall(SystemCallID::CREATE_PROCESS));
}

TEST_F(SystemCallTest, AllocateMemorySystemCall)
{
    // Check if the system call was invoked (no exception thrown)
    EXPECT_NO_THROW(systemCallTable.invokeSystemCall(SystemCallID::ALLOCATE_MEMORY));
}
