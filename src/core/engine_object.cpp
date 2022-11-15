#include "../../include/core/engine_object.hpp"

palace::EngineObject::EngineObject() {
    m_context = nullptr;
    m_parent = nullptr;
    m_id = InvalidId;
    m_index = InvalidId;
    m_references = 0;
    m_deleted = false;
}

palace::EngineObject::~EngineObject() {}

void palace::EngineObject::free() { free_(); }

void palace::EngineObject::setDeleted() {
    if (m_references != 0) {
        PALACE_LOG_WARNING("{} has {} active references",
                           DefaultObjectFormatter(this), m_references);
    } else {
        PALACE_LOG_INFO("{}: deletion flag set",
                           DefaultObjectFormatter(this));
    }

    m_deleted = true;
}

void palace::EngineObject::free_() {
    PALACE_LOG_WARNING("Default free_() called for {}",
                       DefaultObjectFormatter(this));
}
