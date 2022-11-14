#ifndef ATG_PALACE_ENGINE_WINAPI_CONTEXT_HPP
#define ATG_PALACE_ENGINE_WINAPI_CONTEXT_HPP

#include "vulkan_context.hpp"

#include "../../os/winapi/winapi_window_server.hpp"

namespace palace {

class VulkanWinApiContext : public VulkanContext {
    PALACE_OBJECT_DATA(VulkanWinApiContext, GraphicsApiObject,
                       "Top level Vulkan API context for WinAPI.")
public:
    struct Parameters {
        VulkanContext::Parameters baseParameters;
        WinApiWindowServer *windowServer;
    };

public:
    VulkanWinApiContext();
    virtual ~VulkanWinApiContext() override;

    Result initialize(const Parameters &parameters);

protected:
    virtual void getRequiredExtensions(DynamicArray<const char *> &extensions);

private:
    WinApiWindowServer *m_windowServer;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINAPI_CONTEXT_HPP */
