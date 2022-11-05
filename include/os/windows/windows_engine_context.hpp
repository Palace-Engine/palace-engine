#ifndef ATG_PALACE_ENGINE_WINDOWS_ENGINE_CONTEXT_HPP
#define ATG_PALACE_ENGINE_WINDOWS_ENGINE_CONTEXT_HPP

#include "../../core/engine_context.hpp"

#include "windows_application_context.hpp"
#include "../../platform/platform_detection.hpp"
#include "../../platform/platform_includes.hpp"

namespace palace {

class WindowsEngineContext : public EngineContext {
public:
    WindowsEngineContext();
    virtual ~WindowsEngineContext();

#if PALACE_PLATFORM_WINDOWS
    void initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow);
    void free();
#endif

private:
    WindowsApplicationContext m_applicationContext;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOWS_ENGINE_CONTEXT_HPP */
