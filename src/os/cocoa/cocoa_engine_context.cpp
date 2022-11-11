#include "../../../include/os/cocoa/cocoa_engine_context.hpp"

palace::CocoaEngineContext::CocoaEngineContext() : EngineContext(&m_applicationContext) {}

palace::CocoaEngineContext::~CocoaEngineContext() {}

void palace::CocoaEngineContext::initialize() {
    registerApplicationContext();
    m_applicationContext.initialize();
}

void palace::CocoaEngineContext::free() {
    m_applicationContext.free();
    logger().close();
}
