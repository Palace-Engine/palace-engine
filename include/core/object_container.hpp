#ifndef ATG_PALACE_ENGINE_OBJECT_CONTAINER_HPP
#define ATG_PALACE_ENGINE_OBJECT_CONTAINER_HPP

#include "dynamic_array.hpp"

namespace palace {

class ObjectContainerAllocator {
public:
    static HeapAllocator *s_defaultAllocator;

public:
    ObjectContainerAllocator() = delete;
    ObjectContainerAllocator(const ObjectContainerAllocator &) = delete;
    ~ObjectContainerAllocator() = delete;

    static void setDefaultAllocator(HeapAllocator *allocator) {
        s_defaultAllocator = allocator;
    }
};

template<typename T_Base, typename T_Object = T_Base,
         size_t alignment = PALACE_DEFAULT_MEMORY_ALIGNMENT>
class ObjectContainer {
public:
    using BaseContainer = ObjectContainer<T_Base, T_Base, alignment>;

public:
    ObjectContainer() {
        m_allocator = ObjectContainerAllocator::s_defaultAllocator;
    }
    virtual ~ObjectContainer() { free(); }

    template<typename T_NewObject = T_Object>
    inline T_NewObject *create() {
        T_NewObject *const newObject =
                m_allocator->palace_aligned_new(T_NewObject, alignment);
        palace_assert(dynamic_cast<T_Base *>(newObject) != nullptr);

        m_array.append(static_cast<T_Base *>(newObject));

        return newObject;
    }

    inline size_t size() const { return m_array.size(); }

    inline void free(size_t i) {
        m_allocator->palace_aligned_free(m_array[i]);
        m_array.fastRemove(i);
    }

    void free() {
        const size_t n = m_array.size();
        for (size_t i = 0; i < n; ++i) { free(0); }
    }

    inline T_Object *operator[](size_t index) const {
        T_Base *const object = m_array[index];
        palace_assert(dynamic_cast<T_Object *>(object) != nullptr);

        return static_cast<T_Object *>(object);
    }

    inline BaseContainer *toBase() {
        return reinterpret_cast<BaseContainer *>(this);
    }

    DynamicArray<T_Base *> &container() const { return m_array; }

private:
    HeapAllocator *m_allocator = nullptr;
    DynamicArray<T_Base *> m_array;
};

template<typename T_Base, size_t alignment = PALACE_DEFAULT_MEMORY_ALIGNMENT>
using BaseObjectContainer = ObjectContainer<T_Base, T_Base, alignment>;

}// namespace palace

#endif /* ATG_PALACE_ENGINE_OBJECT_CONTAINER_HPP */
