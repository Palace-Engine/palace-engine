#ifndef ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP
#define ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP

#include "engine_context.hpp"

namespace palace {

class EngineObject {
public:
    EngineObject();
    virtual ~EngineObject();

    inline void setContext(EngineContext *context) { m_context = context; }
    inline EngineContext *context() const { return m_context; }
    inline Logger &logger() const { return context()->logger(); }
    inline void addObject(EngineObject *object) {
        object->m_context = m_context;
        object->m_parent = this;
    }

private:
    EngineContext *m_context;
    EngineObject *m_parent;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP */
