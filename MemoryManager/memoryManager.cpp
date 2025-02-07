#include "memoryManager.hpp"

// Memory Map to track allocated and free memory blocks
int MemoryMap::allocateMemory(int size)
{
    std::lock_guard<std::mutex> lock(mtx);
    for (auto &block : memoryBlocks)
    {
        if (!block.allocated && block.size >= size)
        {
            int startAddress = block.start;
            if (block.size > size)
            {
                memoryBlocks.push_back({block.start + size, block.size - size, false});
            }
            block.size = size;
            block.allocated = true;
            std::cout << "Allocated " << size << " bytes at address " << startAddress << "." << std::endl;
            return startAddress;
        }
    }
    std::cout << "Memory allocation failed for " << size << " bytes." << std::endl;
    return -1;
}

void MemoryMap::deallocateMemory(int startAddress)
{
    std::lock_guard<std::mutex> lock(mtx);
    for (auto &block : memoryBlocks)
    {
        if (block.allocated && block.start == startAddress)
        {
            block.allocated = false;
            std::cout << "Deallocated memory at address " << startAddress << "." << std::endl;
            mergeFreeBlocks();
            return;
        }
    }
    std::cout << "No allocated memory found at address " << startAddress << "." << std::endl;
}

void MemoryMap::mergeFreeBlocks()
{
    for (auto it = memoryBlocks.begin(); it != memoryBlocks.end(); ++it)
    {
        auto next = std::next(it);
        if (next != memoryBlocks.end() && !it->allocated && !next->allocated)
        {
            it->size += next->size;
            memoryBlocks.erase(next);
            --it; // Check again from the current position
        }
    }
}

void MemoryMap::displayMemoryMap()
{
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Memory Map:" << std::endl;
    for (const auto &block : memoryBlocks)
    {
        std::cout << "Start: " << block.start << ", Size: " << block.size << ", Allocated: " << (block.allocated ? "Yes" : "No") << std::endl;
    }
}
