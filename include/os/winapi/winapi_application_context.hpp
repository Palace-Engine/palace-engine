#ifndef ATG_PALACE_ENGINE_WINDOWS_APPLICATION_CONTEXT_HPP
#define ATG_PALACE_ENGINE_WINDOWS_APPLICATION_CONTEXT_HPP

#include "../application_context.hpp"

#include "../../platform/platform_detection.hpp"
#include "../../platform/platform_includes.hpp"
#include "winapi_window_server.hpp"

namespace palace {

class WinApiEngineContext;
class WinApiApplicationContext : public ApplicationContext {
    PALACE_OBJECT_DATA(WinApiApplicationContext, ApplicationContext,
                       "Application-level context for Windows applications.");

    friend WinApiEngineContext;

public:
#if PALACE_PLATFORM_WINDOWS
    struct Parameters {
        HINSTANCE hInstance;
        HINSTANCE hPrevInstance;
        LPSTR lpCmdLine;
        int nCmdShow;
    };
#else
    using Parameters = DefaultParameters;
#endif

public:
    WinApiApplicationContext();
    virtual ~WinApiApplicationContext() override;

    void initialize(const Parameters &params);

    virtual GraphicsContext *
    createVulkanContext(const VulkanVersion &version) override;
    WinApiWindowServer &windowServer() { return m_windowServer; }

public:
#if PALACE_PLATFORM_WINDOWS
    HINSTANCE currentInstance() const;
    HINSTANCE previousInstance() const;
    int initialDisplayCommand() const;
#endif

private:
#if PALACE_PLATFORM_WINDOWS
    HINSTANCE m_currentInstance;
    HINSTANCE m_previousInstance;
    int m_initialDisplayCommand;
#endif

    WinApiWindowServer m_windowServer;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOWS_APPLICATION_CONTEXT_HPP */
