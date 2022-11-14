#include "../../include/os/application_context.hpp"

#include "../../include/graphics/vulkan/vulkan_context.hpp"

palace::ApplicationContext::ApplicationContext(
        Platform platform, WindowServer *windowServer)
    : PlatformObject(platform), m_windowServer(windowServer) {}

palace::ApplicationContext::~ApplicationContext() {}

void palace::ApplicationContext::free() { internalFree(); }

void palace::ApplicationContext::initialize(const DefaultParameters &params) {
    for (int i = 0; i < params.argc; ++i) {
        addCommandLineArgument((*params.argv)[i]);
    }
}

void palace::ApplicationContext::addCommandLineArgument(const string &s) {
    PALACE_LOG_INFO("Adding command line argument: {}", s.c_str());
    m_commandLineArguments.append(s);
}

void palace::ApplicationContext::internalFree() {
    if (m_windowServer != nullptr) { m_windowServer->free(); }
}

palace::VulkanVersion
palace::ApplicationContext::highestSupportedVulkanVersion() const {
    return VulkanContext::highestSupportedVersion();
}
