#include "../../../include/os/cocoa/cocoa_application_context.hpp"

palace::CocoaApplicationContext::CocoaApplicationContext() : ApplicationContext(Platform::MacOS, &m_windowServer) {
    palace_assert(PALACE_PLATFORM_MACOS);
}

palace::CocoaApplicationContext::~CocoaApplicationContext() {}

void palace::CocoaApplicationContext::initialize() {
    addObject(&m_windowServer);
    
    m_context = cocoa_interface::createContext();
}

void palace::CocoaApplicationContext::free() {
    cocoa_interface::freeContext(m_context);
}
