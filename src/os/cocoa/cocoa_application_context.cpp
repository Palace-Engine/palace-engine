#include "../../../include/os/cocoa/cocoa_application_context.hpp"

palace::CocoaApplicationContext::CocoaApplicationContext()
    : ApplicationContext(Platform::MacOS, &m_windowServer) {
    palace_assert(PALACE_PLATFORM_MACOS);
}

palace::CocoaApplicationContext::~CocoaApplicationContext() {}

void palace::CocoaApplicationContext::initialize() {
    registerObject(&m_windowServer);
    m_windowServer.addReference();

#if PALACE_SUPPORTS_COCOA
    m_context = cocoa_interface::createContext();
#endif
}

void palace::CocoaApplicationContext::internalFree() {
    ApplicationContext::internalFree();

#if PALACE_SUPPORTS_COCOA
    cocoa_interface::freeContext(m_context);
#endif
}

palace::GraphicsContext *palace::CocoaApplicationContext::createVulkanContext(
        const VulkanVersion &version) {
    return nullptr;
}
