#ifndef ATG_PALACE_ENGINE_HEAP_ALLOCATOR_H
#define ATG_PALACE_ENGINE_HEAP_ALLOCATOR_H

#include "../debug/assert.hpp"
#include "alloc.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <new>
#include <string_view>
#include <vector>

#define debug_palace_aligned_new(type, alignment, ...)                         \
    palace::HeapAllocator::get().allocateDebug<type, alignment>(               \
            __FILE__, __LINE__ __VA_OPT__(, ) __VA_ARGS__)
#define debug_palace_new(type, ...)                                            \
    palace::HeapAllocator::get().allocateDebug<type>(__VA_ARGS__ __FILE__,     \
                                                     __LINE__)

namespace palace {

class HeapAllocator {
private:
    struct MemoryBlock {
        void *address;
        size_t size;
    };

public:
    template<typename T_Data, int alignment = 1>
    static inline T_Data *allocate() {
        void *mem = palace_alloc(alignment, sizeof(T_Data));
        return new (mem) T_Data;
    }

    template<typename T_Data, int alignment = 1>
    T_Data *allocateDebug(std::string_view srcFile, int line,
                          std::string_view msg = "") {
        T_Data *data = allocate<T_Data, alignment>();

        MemoryBlock new_block;
        new_block.address = static_cast<void *>(data);
        new_block.size = sizeof(T_Data);
        m_memoryBlocks.push_back(new_block);

        m_memoryUsed += new_block.size;
        ++m_totalAllocations;

        return data;
    }

    template<typename T_Data, int alignment = 1>
    T_Data *allocate(int n) {
        void *mem = palace_alloc(alignment, sizeof(T_Data));
        T_Data *data = new (mem) T_Data;

#ifdef PALACE_DEBUG
        MemoryBlock new_block;
        new_block.address = data;
        new_block.size = sizeof(T_Data) * n;
        m_memoryBlocks.push_back(new_block);

        m_memoryUsed += new_block.size;
        ++m_totalAllocations;
#endif// PALACE_DEBUG

        return data;
    }

    template<typename T_Data>
    void free(T_Data *&memory) {
        bool found = false;
        for (size_t i = 0; i < m_memoryBlocks.size(); ++i) {
            if (m_memoryBlocks[i].address == memory) {
                m_memoryUsed -= m_memoryBlocks[i].size;

                m_memoryBlocks[i] = m_memoryBlocks.back();
                m_memoryBlocks.resize(m_memoryBlocks.size() - 1);

                found = true;
                break;
            }
        }

        palace_assert(found);

        palace_free(memory);
        memory = nullptr;
    }

    inline size_t getMemoryUsed() { return m_memoryUsed; }
    inline size_t getActiveAllocations() { return m_memoryBlocks.size(); }
    inline size_t getTotalAllocations() { return m_totalAllocations; }

    inline static HeapAllocator &get() {
        static HeapAllocator instance;
        return instance;
    }

private:
    HeapAllocator(const HeapAllocator &) = delete;
    HeapAllocator() {}
    ~HeapAllocator() {
        palace_assert(getActiveAllocations() == 0, "Unfreed memory");
    }

private:
    size_t m_memoryUsed = 0;
    size_t m_totalAllocations = 0;
    std::vector<MemoryBlock> m_memoryBlocks;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_HEAP_ALLOCATOR_H */