#ifndef ATG_PALACE_ENGINE_HEAP_ALLOCATOR_H
#define ATG_PALACE_ENGINE_HEAP_ALLOCATOR_H

#include "../debug/assert.hpp"
#include "alloc.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <mutex>
#include <new>
#include <string_view>
#include <vector>

#define PALACE_DEFAULT_MEMORY_ALIGNMENT __STDCPP_DEFAULT_NEW_ALIGNMENT__

#define debug_palace_new(type, ...)                                            \
    allocateDebug<type>(__FILE__, __LINE__ __VA_OPT__(, ) __VA_ARGS__)
#define debug_palace_free(memory) freeDebug(memory)

#define debug_palace_aligned_new(type, alignment, ...)                         \
    allocateDebug<type, (alignment)>(__FILE__,                                 \
                                     __LINE__ __VA_OPT__(, ) __VA_ARGS__)
#define debug_palace_aligned_free(memory) freeDebug(memory)

#define debug_palace_new_array(type, n, ...)                                   \
    allocateArrayDebug<type>(n, __FILE__, __LINE__ __VA_OPT__(, ) __VA_ARGS__)
#define debug_palace_free_array(memory) freeArrayDebug(memory)

#define debug_palace_aligned_new_array(type, alignment, n, ...)                \
    allocateArrayDebug<type, (alignment)>(n, __FILE__,                         \
                                          __LINE__ __VA_OPT__(, ) __VA_ARGS__)
#define debug_palace_aligned_free_array(memory) freeArrayDebug(memory)

#define release_palace_new(type) allocate<type>()
#define release_palace_free(memory) free(memory)

#define release_palace_aligned_new(type, alignment)                            \
    allocate<type, (alignment)>()
#define release_palace_aligned_free(memory) free(memory)

#define release_palace_new_array(type, n) allocate<type>(n)
#define release_palace_free_array(memory) freeArray(memory)

#define release_palace_aligned_new_array(type, alignment, n)                   \
    allocate<type, (alignment)>(n)
#define release_palace_aligned_free_array(memory) freeArray(memory)

#if defined(PALACE_DEBUG)
#define palace_new debug_palace_new
#define palace_free debug_palace_free
#define palace_aligned_new debug_palace_aligned_new
#define palace_aligned_free debug_palace_aligned_free
#define palace_new_array debug_palace_new_array
#define palace_free_array debug_palace_free_array
#define palace_aligned_new_array debug_palace_aligned_new_array
#define palace_aligned_free_array debug_palace_aligned_free_array
#elif defined(PALACE_RELEASE)
#define palace_new release_palace_new
#define palace_free release_palace_free
#define palace_aligned_new release_palace_aligned_new
#define palace_aligned_free release_palace_aligned_free
#define palace_new_array release_palace_new_array
#define palace_free_array release_palace_free_array
#define palace_aligned_new_array release_palace_aligned_new_array
#define palace_aligned_free_array release_palace_aligned_free_array
#endif

namespace palace {

class HeapAllocator {
private:
    struct MemoryBlock {
        void *address = nullptr;
        std::string_view filename = "";
        std::string_view message = "";
        int line = 0;
        size_t size = 0;
        size_t allocationId = 0;
    };

    struct BlockInformation {
        void *actualAddress;
        size_t n;
    };
    
    static constexpr bool validAlignment(size_t alignment) {
        return (alignment == 0)
            ? false
            : (alignment & (alignment - 1)) == 0;
    }
    
    static constexpr size_t alignedSize(size_t size, size_t alignment) {
        const size_t sizeModAlignment = size & (alignment - 1);
        return (sizeModAlignment == 0)
            ? size
            : size + (alignment - sizeModAlignment);
    }

public:
    HeapAllocator(const HeapAllocator &) = delete;
    HeapAllocator() {}
    ~HeapAllocator() {
        palace_assert(getActiveAllocations() == 0, "Unfreed memory");
    }

    // Alignment is a template parameter for the following reasons:
    // - In case aligned allocations are found to have a performance
    //   cost and need to be separated from regular allocations
    //   without the use of an if-statement.
    // - Simplifies the syntax of the macros defined above
    template<typename T_Data,
             size_t alignment = PALACE_DEFAULT_MEMORY_ALIGNMENT>
    static inline T_Data *allocate() {
        static_assert(validAlignment(alignment));
        
        void *const mem = palace_mem_alloc(
                alignment, alignedSize(sizeof(T_Data), alignment));
        return new (mem) T_Data;
    }

    template<typename T_Data>
    void free(T_Data *&memory) {
        palace_mem_free(memory);
        memory = nullptr;
    }

    template<typename T_Data,
             size_t alignment = PALACE_DEFAULT_MEMORY_ALIGNMENT>
    static inline T_Data *allocateArray(size_t n) {
        static_assert(validAlignment(alignment));
                
        constexpr size_t dataBlockSize =
                alignment *
                ((sizeof(size_t) + sizeof(BlockInformation) + alignment - 1) /
                 alignment);

        void *const mem =
                palace_mem_alloc(alignment,
                                 alignedSize(dataBlockSize + sizeof(T_Data) * n,
                                             alignment));
        BlockInformation *info = new (mem) BlockInformation;
        info->actualAddress = mem;
        info->n = n;

        void *const data = reinterpret_cast<void *>(
                static_cast<uint8_t *>(mem) + dataBlockSize);
        size_t *alignmentStorage = static_cast<size_t *>(data) - 1;
        *alignmentStorage = alignment;

        return new (data) T_Data;
    }

    template<typename T_Data>
    void freeArray(T_Data *&memory) {
        const size_t alignment = *(reinterpret_cast<size_t *>(memory) - 1);
        const size_t dataBlockSize =
                alignment *
                ((sizeof(size_t) + sizeof(BlockInformation) + alignment - 1) /
                 alignment);

        const BlockInformation *info = reinterpret_cast<BlockInformation *>(
                reinterpret_cast<uint8_t *>(memory) - dataBlockSize);

        for (size_t i = 0; i < info->n; ++i) { memory[i].~T_Data(); }

        palace_mem_free(info->actualAddress);
        memory = nullptr;
    }

    template<typename T_Data,
             size_t alignment = PALACE_DEFAULT_MEMORY_ALIGNMENT>
    T_Data *allocateDebug(std::string_view srcFile, int line,
                          std::string_view msg = "") {
        T_Data *const data = allocate<T_Data, alignment>();
        trackMemoryAllocation(static_cast<void *>(data), sizeof(T_Data),
                              srcFile, line, msg);

        return data;
    }

    template<typename T_Data>
    inline void freeDebug(T_Data *&memory) {
        palace_assert(trackMemoryFree(static_cast<void *>(memory)));

        memory->~T_Data();

        free(memory);
    }

    template<typename T_Data,
             size_t alignment = PALACE_DEFAULT_MEMORY_ALIGNMENT>
    T_Data *allocateArrayDebug(size_t n, std::string_view srcFile, int line,
                               std::string_view msg = "") {
        T_Data *const data = allocateArray<T_Data, alignment>(n);
        trackMemoryAllocation(static_cast<void *>(data), n * sizeof(T_Data),
                              srcFile, line, msg);

        return data;
    }

    template<typename T_Data>
    inline void freeArrayDebug(T_Data *&memory) {
        palace_assert(trackMemoryFree(static_cast<void *>(memory)));

        freeArray(memory);
    }

    inline size_t getCurrentAllocationId() { return m_allocationId; }
    inline size_t getMemoryUsed() { return m_memoryUsed; }
    inline size_t getActiveAllocations() { return m_memoryBlocks.size(); }
    inline size_t getTotalAllocations() { return m_totalAllocations; }
    const MemoryBlock &getActiveAllocation(size_t i) { return m_memoryBlocks[i]; }

    void clearRecords() {
        std::lock_guard<std::mutex> guard(m_trackingGuard);
        m_memoryBlocks.clear();
        m_memoryUsed = 0;
    }

private:
    void trackMemoryAllocation(void *address, size_t size,
                               std::string_view filename, int line,
                               std::string_view message) {
        std::lock_guard<std::mutex> guard(m_trackingGuard);

        MemoryBlock newBlock;
        newBlock.address = address;
        newBlock.size = size;
        newBlock.filename = filename;
        newBlock.message = message;
        newBlock.line = line;
        newBlock.allocationId = m_allocationId++;
        m_memoryBlocks.push_back(newBlock);

        m_memoryUsed += size;
        ++m_totalAllocations;
    }

    bool trackMemoryFree(void *address) {
        std::lock_guard<std::mutex> guard(m_trackingGuard);

        for (size_t i = 0; i < m_memoryBlocks.size(); ++i) {
            if (m_memoryBlocks[i].address == address) {
                m_memoryUsed -= m_memoryBlocks[i].size;

                m_memoryBlocks[i] = m_memoryBlocks.back();
                m_memoryBlocks.resize(m_memoryBlocks.size() - 1);

                return true;
            }
        }

        return false;
    }

private:
    std::mutex m_trackingGuard;
    size_t m_memoryUsed = 0;
    size_t m_totalAllocations = 0;
    size_t m_allocationId = 0;
    std::vector<MemoryBlock> m_memoryBlocks;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_HEAP_ALLOCATOR_H */
