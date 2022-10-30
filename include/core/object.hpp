#ifndef ATG_PALACE_ENGINE_OBJECT_HPP
#define ATG_PALACE_ENGINE_OBJECT_HPP

#include "dynamic_array.hpp"
#include "object_container.hpp"

namespace palace {

class Object {
    using Index = size_t;
    using Id = size_t;

private:
    Id m_id;
    T_Root *m_root;
    T_Context *m_context;
    Index m_localIndex;

    BaseObjectContainer<CurrentTemplate> m_objects;

    Id m_nextChildId;
};

template<typename T_Root, typename T_Context>
class SpecializedObject {
private:
    using CurrentTemplate = Object<T_Root, T_Context>;

public:
    static constexpr Id InvalidId = -1;
    static constexpr Index InvalidIndex = -1;

public:
    template<typename T_Base, typename T_Object = T_Base>
    class ObjectList {
    public:
        ObjectList() = delete;
        ObjectList(CurrentTemplate *parent) {
            static_assert(std::is_base_of<T_Base, T_Object>::value);
            m_parent = parent;
        }

        template<typename T_SpecificObject = T_Object, typename... T_Args>
        inline T_SpecificObject *create(T_Args... t_args) {
            T_SpecificObject *newObject =
                    m_parent->create<T_SpecificObject>(t_args...);
            m_objects.append(static_cast<T_Object *>(newObject));
            return newObject;
        }

        inline void free(T_Object *&object) {
            m_objects.fastRemoveFirst(object);
            m_parent->free(object);
        }

        inline size_t size() const { return m_objects.size(); }
        inline T_Object *operator[](size_t index) const {
            return m_objects[index];
        }

        inline ObjectList<T_Base, T_Base> *toBase() {
            return reinterpret_cast<ObjectList<T_Base, T_Base> *>(this);
        }

    private:
        CurrentTemplate *m_parent;
        DynamicArray<T_Object *> m_objects;
    };

    template<typename T_Object, typename T_Base>
    friend class ObjectList;

public:
    virtual ~Object() {}

    void initialize() {}

    inline Id id() const { return m_id; }
    inline Object *root() const { return m_root; }
    inline Object *context() const { return m_context; }
    inline size_t activeObjects() const { return m_objects.size(); }

protected:
    Object() {
        m_id = InvalidId;
        m_localIndex = InvalidIndex;
        m_root = this;
        m_context = nullptr;
        m_nextChildId = 0;
    };

private:
    Object(const Object &) = delete;

    inline void construct(T_Root *root, T_Context *context, Id id,
                          Index localIndex) {
        m_root = root;
        m_context = context;
        m_id = id;
        m_localIndex = localIndex;
    }

    template<typename T_NewObject>
    inline T_NewObject *create() {
        T_NewObject *newObject = m_objects.create<T_NewObject>();
        static_cast<CurrentTemplate *>(newObject)->construct(
                m_root, this, m_root->m_nextChildId++, m_objects.size() - 1);

        return newObject;
    }

    template<typename T_Object>
    inline void free(T_Object *&object) {
        const Index index =
                static_cast<CurrentTemplate *>(object)->m_localIndex;
        m_objects.free(index);

        if (m_objects.size() > 0) { m_objects[index]->m_localIndex = index; }
        object = nullptr;
    }

private:
    Id m_id;
    T_Root *m_root;
    T_Context *m_context;
    Index m_localIndex;

    BaseObjectContainer<CurrentTemplate> m_objects;

    Id m_nextChildId;
};

}// namespace palace

#endif// ATG_PALACE_ENGINE_OBJECT_HPP
