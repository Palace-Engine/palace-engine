#ifndef ATG_PALACE_ENGINE_OBJECT_CONTAINER_HPP
#define ATG_PALACE_ENGINE_OBJECT_CONTAINER_HPP

#include "dynamic_array.hpp"

namespace palace {

template<typename T_Object, typename T_Base,
         size_t alignment = PALACE_DEFAULT_MEMORY_ALIGNMENT>
class ObjectContainer {
public:
    ObjectContainer() {}
    virtual ~ObjectContainer() { destroy(); }

    template<typename T_NewObject = T_Object>
    inline T_Object *create() {
        T_Object *const newObject = palace_aligned_new(T_NewObject, alignment);
        palace_assert(dynamic_cast<T_Base *>(newObject) != nullptr);

        m_array.append(static_cast<T_Base *>(newObject));

        return newObject;
    }

    inline void free(size_t i) {
        m_array.fastRemove(i);
        palace_aligned_free(m_array[i]);
    }

    void destroy() {
        const size_t n = m_array.size();
        for (size_t i = 0; i < n; ++i) { free(0); }
    }

    inline T_Object *operator[](size_t index) const {
        T_Base *const object = m_array[index];
        palace_assert(dynamic_cast<T_Object *>(object) != nullptr);

        return static_cast<T_Object *>(object);
    }

    DynamicArray<T_Base *> &container() const { return m_array; }

private:
    DynamicArray<T_Base *> m_array;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_OBJECT_CONTAINER_HPP */
