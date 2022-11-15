#include "../../include/os/application_context.hpp"

#include "../../include/graphics/vulkan/vulkan_context.hpp"

palace::ApplicationContext::ApplicationContext(Platform platform,
                                               WindowServer *windowServer)
    : PlatformObject(platform), m_windowServer(windowServer) {}

palace::ApplicationContext::~ApplicationContext() {}

void palace::ApplicationContext::free() {
    PALACE_LOG_INFO("Freeing application context");

    internalFree();

    if (m_windowServer != nullptr) {
        m_windowServer->removeReference();
        m_windowServer->setDeleted();
        m_windowServer->free();

        if (m_windowServer->references() != 0) {
            PALACE_LOG_WARNING("{} still has {} active references",
                               DefaultObjectFormatter(m_windowServer),
                               m_windowServer->references());
        }
    }
}

void palace::ApplicationContext::freeGraphicsContext(
        GraphicsContext *&context) {
    context->setDeleted();
    context->free();

}

void palace::ApplicationContext::initialize(const DefaultParameters &params) {
    for (int i = 0; i < params.argc; ++i) {
        addCommandLineArgument((*params.argv)[i]);
    }
}

void palace::ApplicationContext::addCommandLineArgument(const string &s) {
    PALACE_LOG_INFO("Adding command line argument: {}", s.c_str());
    m_commandLineArguments.append(s);
}

void palace::ApplicationContext::internalFree() {}

palace::VulkanVersion
palace::ApplicationContext::highestSupportedVulkanVersion() const {
    return VulkanContext::highestSupportedVersion();
}
