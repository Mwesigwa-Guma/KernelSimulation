#include <vector>
#include <iostream>

// Memory Block structure
struct MemoryBlock {
    int start;
    int size;
    bool allocated;
};


// Memory Map to track allocated and free memory blocks
class MemoryMap {
private:
    std::mutex mtx;
    const int totalMemorySize = 2048;

public:
    MemoryMap() {
        memoryBlocks.push_back({0, totalMemorySize, false}); // Entire memory initially free
    }

    int allocateMemory(int size);
    void deallocateMemory(int startAddress);
    void mergeFreeBlocks();
    void displayMemoryMap();

    std::vector<MemoryBlock> memoryBlocks;
};
