#ifndef ATG_PALACE_ENGINE_VULKAN_CONTEXT_HPP
#define ATG_PALACE_ENGINE_VULKAN_CONTEXT_HPP

#include "../graphics_context.hpp"

#include "vulkan_includes.hpp"
#include "vulkan_version.hpp"

namespace palace {

class VulkanContext : public GraphicsContext {
    PALACE_OBJECT_DATA(VulkanContext, GraphicsContext,
                       "Top level Vulkan API context.");

public:
    struct Parameters {
        GraphicsContext::Parameters
            baseParameters;
        VulkanVersion version;
    };

public:
    virtual ~VulkanContext() override;

    virtual void queryDevices() override;
    virtual size_t deviceCount() override;
    virtual string deviceName(size_t i) override;

#if PALACE_SUPPORTS_VULKAN
    VkInstance vulkanInstance() const { return m_instance; }
    static VulkanVersion highestSupportedVersion();
    static bool supports(const palace::VulkanVersion &version);
#endif

protected:
    VulkanContext(Platform platform);

    Result initialize(const Parameters &parameters);
    virtual void getRequiredExtensions(DynamicArray<const char *> &extensions) = 0;

protected:
#if PALACE_SUPPORTS_VULKAN
    VkInstance m_instance;
#endif
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_VULKAN_CONTEXT_HPP */
