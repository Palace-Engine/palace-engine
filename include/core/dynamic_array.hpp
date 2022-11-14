#ifndef ATG_PALACE_ENGINE_DYNAMIC_ARRAY_HPP
#define ATG_PALACE_ENGINE_DYNAMIC_ARRAY_HPP

#include "../debug/assert.hpp"
#include "../memory/heap_allocator.hpp"
#include "../types/limits.hpp"

#include <algorithm>
#include <cstring>
#include <vector>

namespace palace {

class DynamicArrayAllocator {
public:
    static HeapAllocator *s_defaultAllocator;

public:
    DynamicArrayAllocator() = delete;
    DynamicArrayAllocator(const DynamicArrayAllocator &) = delete;
    ~DynamicArrayAllocator() = delete;

    static void setDefaultAllocator(HeapAllocator *allocator) {
        s_defaultAllocator = allocator;
    }
};

template<typename T_Data>
class DynamicArray {
public:
    static constexpr size_t InvalidIndex = size_t_max;

public:
    DynamicArray() { m_allocator = DynamicArrayAllocator::s_defaultAllocator; }
    ~DynamicArray() { free(); }

    void setAllocator(HeapAllocator *allocator) { m_allocator = allocator; }
    HeapAllocator *allocator() const { return m_allocator; }

    const T_Data &append(const T_Data &data) {
        if (m_size >= m_capacity) { resize(m_capacity * 2 + 1); }

        return m_data[m_size++] = data;
    }

    const T_Data *data() const { return m_data; }
    T_Data *writeable() const { return m_data; }

    template<class... T_Initializer>
    const T_Data &emplace(T_Initializer &&...args) {
        palace_assert(m_size < m_capacity, "Insufficient capacity");

        return *(new (reinterpret_cast<void *>(&m_data[m_size++]))
                         T_Data(args...));
    }

    const T_Data &insert(const T_Data &data, size_t index) {
        palace_assert(index <= m_size, "Index out of range");

        if (m_size >= m_capacity) { resize(m_capacity * 2 + 1); }

        std::memmove(m_data + index + 1, m_data + index,
                     sizeof(T_Data) * (m_size - index));
        ++m_size;

        return m_data[index] = data;
    }

    inline void fastRemove(size_t index) {
        palace_assert(index < m_size, "Index out of range");

        m_data[index] = m_data[--m_size];
    }

    inline void remove(size_t index) {
        palace_assert(index < m_size, "Index out of range");

        std::memmove(m_data + index, m_data + index + 1,
                     sizeof(T_Data) * (--m_size - index));
    }

    size_t findFirst(const T_Data &element) const {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_data[i] == element) { return i; }
        }

        return InvalidIndex;
    }

    void fastRemoveFirst(const T_Data &element) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_data[i] == element) {
                fastRemove(i);
                return;
            }
        }
    }

    void removeFirst(const T_Data &element) {
        for (int i = 0; i < m_size; ++i) {
            if (m_data[i] == element) {
                remove(i);
                return;
            }
        }
    }

    inline T_Data &operator[](size_t index) const {
        assert(index < m_size);
        return m_data[index];
    }

    void truncate(size_t size) { m_size = (size < m_size) ? size : m_size; }

    void resize(size_t size) {
        T_Data *newData = m_allocator->palace_new_array(T_Data, size);
        const size_t newSize = (size < m_size) ? size : m_size;

        if (m_data != nullptr) {
            std::memcpy(newData, m_data, sizeof(T_Data) * newSize);
            free();
        }

        m_size = newSize;
        m_capacity = size;
        m_data = newData;
    }

    void free() {
        if (m_data != nullptr) { m_allocator->palace_free_array(m_data); }

        m_capacity = 0;
        m_size = 0;
    }

    inline size_t size() const { return m_size; }
    inline size_t capacity() const { return m_capacity; }

private:
    HeapAllocator *m_allocator = nullptr;
    size_t m_capacity = 0;
    size_t m_size = 0;
    T_Data *m_data = nullptr;
};

}// namespace palace

#endif// ATG_PALACE_ENGINE_DYNAMIC_ARRAY_HPP
