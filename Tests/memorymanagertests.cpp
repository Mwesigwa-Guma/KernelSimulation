#include "../MemoryManager/memoryManager.hpp"
#include <gtest/gtest.h>
#include <iostream>

// Test fixture for Memory Manager tests
class MemoryMapTest : public ::testing::Test
{
protected:
    MemoryMap memoryMap;

    MemoryMapTest() : memoryMap() {}

    void SetUp() override
    {
        // Initialize memory manager if needed
    }

    void TearDown() override
    {
        std::cout << "TearDown created resources" << std::endl;
    }
};

// Test case to check if memory allocation works correctly
TEST_F(MemoryMapTest, AllocateMemory)
{
    int startAddress = memoryMap.allocateMemory(1024); // Allocate 1KB of memory
    EXPECT_EQ(startAddress, 0); // Check if the memory was allocated
    EXPECT_EQ(memoryMap.memoryBlocks.size(), 2); // Check if the memory block was added
}

// Test case to check if memory deallocation works correctly
TEST_F(MemoryMapTest, DeallocateMemory)
{
    int startAddress = memoryMap.allocateMemory(1024); // Allocate 1KB of memory
    EXPECT_NE(startAddress, 1); // Check if the memory was allocated

    memoryMap.deallocateMemory(1024); // Deallocate the memory
    // Check if the memory was deallocated (no exception thrown)
    EXPECT_NO_THROW(memoryMap.deallocateMemory(0));
}

// Test case to display memory
TEST_F(MemoryMapTest, DisplayMemoryMap)
{
    memoryMap.displayMemoryMap(); // Display the memory map
    // Check if the memory map was displayed (no exception thrown)
    EXPECT_NO_THROW(memoryMap.displayMemoryMap());
}
