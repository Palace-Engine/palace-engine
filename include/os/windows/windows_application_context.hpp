#ifndef ATG_PALACE_ENGINE_WINDOWS_APPLICATION_CONTEXT_HPP
#define ATG_PALACE_ENGINE_WINDOWS_APPLICATION_CONTEXT_HPP

#include "../application_context.hpp"

#include "../../platform/platform_detection.hpp"
#include "../../platform/platform_includes.hpp"
#include "windows_window_server.hpp"

namespace palace {

class WindowsEngineContext;
class WindowsApplicationContext : public ApplicationContext {
    PALACE_OBJECT_DATA(WindowsApplicationContext, ApplicationContext,
                       "Application-level context for Windows applications.");

    friend WindowsEngineContext;

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
    WindowsApplicationContext();
    virtual ~WindowsApplicationContext() override;

    void initialize(const Parameters &params);

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

    WindowsWindowServer m_windowServer;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOWS_APPLICATION_CONTEXT_HPP */
