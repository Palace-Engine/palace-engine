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

template<typename T_Base, size_t alignment = PALACE_DEFAULT_MEMORY_ALIGNMENT>
class BaseObjectContainer {
public:
    BaseObjectContainer() {}
    virtual ~BaseObjectContainer() {}

    virtual size_t size() const = 0;
    virtual T_Base *get(size_t i) const = 0;
    virtual void free(size_t i) = 0;
    virtual void freeBase(T_Base *object) = 0;
    virtual void free() = 0;
    inline T_Base *operator[](size_t i) const { return get(i); }
};

template<typename T_Base, typename T_Object,
         size_t alignment = PALACE_DEFAULT_MEMORY_ALIGNMENT>
class ObjectContainer : public BaseObjectContainer<T_Base, alignment> {
    using T_BaseContainer = BaseObjectContainer<T_Base, alignment>;

public:
    ObjectContainer() {
        m_allocator = ObjectContainerAllocator::s_defaultAllocator;
    }
    virtual ~ObjectContainer() { free(); }

    virtual inline size_t size() const override { return m_array.size(); }
    virtual inline T_Base *get(size_t i) const override {
        return static_cast<T_Base *>(m_array[i]);
    }
    virtual inline void free(size_t i) override {
        m_allocator->palace_aligned_free(m_array[i]);
        m_array.fastRemove(i);
    }
    virtual inline void freeBase(T_Base *object) override {
        free(findFirstBase(object));
    }
    inline void free(T_Object *object) { free(findFirst(object)); }

    template<typename T_NewObject = T_Object>
    inline T_NewObject *create() {
        T_NewObject *const newObject =
                m_allocator->palace_aligned_new(T_NewObject, alignment);
        m_array.append(static_cast<T_Object *>(newObject));

        return newObject;
    }

    inline size_t findFirst(const T_Object *object) const {
        const size_t size = m_array.size();
        for (size_t i = 0; i < size; ++i) {
            if (m_array[i] == object) { return i; }
        }

        return static_cast<size_t>(-1);
    }

    inline size_t findFirstBase(const T_Base *object) const {
        const size_t size = m_array.size();
        for (size_t i = 0; i < size; ++i) {
            if (static_cast<T_Base *>(m_array[i]) == object) { return i; }
        }

        return static_cast<size_t>(-1);
    }

    virtual void free() override {
        const size_t n = m_array.size();
        for (size_t i = 0; i < n; ++i) { free(static_cast<size_t>(0)); }
    }

    inline T_Object *operator[](size_t index) const {
        T_Object *const object = m_array[index];
        return object;
    }

    DynamicArray<T_Object *> &container() const { return m_array; }
    T_BaseContainer *base() {
        return static_cast<T_BaseContainer *>(this);
    }

private:
    HeapAllocator *m_allocator = nullptr;
    DynamicArray<T_Object *> m_array;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_OBJECT_CONTAINER_HPP */
