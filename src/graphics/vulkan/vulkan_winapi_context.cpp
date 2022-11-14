#include "../../../include/graphics/vulkan/vulkan_winapi_context.hpp"

palace::VulkanWinApiContext::~VulkanWinApiContext() {}

palace::Result palace::VulkanWinApiContext::initialize(
        const Parameters &parameters) {
    PALACE_LOG_INFO("Initializing WINAPI Vulkan context");
    m_windowServer = parameters.windowServer;
    return VulkanContext::initialize(parameters.baseParameters);
}

palace::VulkanWinApiContext::VulkanWinApiContext()
    : VulkanContext(Platform::Windows) {
    m_windowServer = nullptr;
}

void palace::VulkanWinApiContext::getRequiredExtensions(
        DynamicArray<const char *> &extensions) {
#if PALACE_SUPPORTS_WINAPI
    extensions.append(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#endif
}
