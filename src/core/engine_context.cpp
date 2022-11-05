#include "../../include/core/engine_context.hpp"

#include "../../include/os/application_context.hpp"

palace::EngineContext::EngineContext(ApplicationContext *applicationContext) {
    m_currentId = 0;
    m_applicationContext = applicationContext;
}

palace::EngineContext::~EngineContext() {}

void palace::EngineContext::registerApplicationContext() {
    m_applicationContext->m_id = newId();
    m_applicationContext->m_context = this;
    m_applicationContext->m_parent = nullptr;
}
