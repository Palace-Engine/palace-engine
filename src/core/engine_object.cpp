#include "../../include/core/engine_object.hpp"

palace::EngineObject::EngineObject() {
    m_context = nullptr;
    m_parent = nullptr;
    m_id = InvalidId;
}

palace::EngineObject::~EngineObject() {}
