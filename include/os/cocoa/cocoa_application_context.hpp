#ifndef ATG_PALACE_ENGINE_COCOA_APPLICATION_CONTEXT_HPP
#define ATG_PALACE_ENGINE_COCOA_APPLICATION_CONTEXT_HPP

#include "../application_context.hpp"

#include "../../platform/platform_detection.hpp"
#include "../../platform/platform_includes.hpp"
#include "cocoa_window_server.hpp"

namespace palace {

class CocoaEngineContext;
class CocoaApplicationContext : public ApplicationContext {
    PALACE_OBJECT_DATA(CocoaApplicationContext, ApplicationContext,
                       "Application-level context for MacOS applications.");

    friend CocoaEngineContext;

public:
    CocoaApplicationContext();
    virtual ~CocoaApplicationContext();

    void initialize();

    virtual GraphicsContext *
    createVulkanContext(const VulkanVersion &version) override;

protected:
    virtual void internalFree() override;

private:
    CocoaWindowServer m_windowServer;

#if PALACE_SUPPORTS_COCOA
    cocoa_interface::ContextHandle m_context;
#endif
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_COCOA_APPLICATION_CONTEXT_HPP */
