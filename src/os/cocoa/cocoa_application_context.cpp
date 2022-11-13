#include "../../../include/os/cocoa/cocoa_application_context.hpp"

palace::CocoaApplicationContext::CocoaApplicationContext()
    : ApplicationContext(Platform::MacOS, &m_windowServer) {
    palace_assert(PALACE_PLATFORM_MACOS);
}

palace::CocoaApplicationContext::~CocoaApplicationContext() {}

void palace::CocoaApplicationContext::initialize() {
    addObject(&m_windowServer);

#if PALACE_SUPPORTS_COCOA
    m_context = cocoa_interface::createContext();
#endif
}

void palace::CocoaApplicationContext::free() {
#if PALACE_SUPPORTS_COCOA
    cocoa_interface::freeContext(m_context);
#endif
}
