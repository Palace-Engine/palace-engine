#include "../../../include/os/windows/windows_engine_context.hpp"

palace::WindowsEngineContext::WindowsEngineContext()
    : EngineContext(&m_applicationContext) {}

palace::WindowsEngineContext::~WindowsEngineContext() {}

#if PALACE_PLATFORM_WINDOWS
void palace::WindowsEngineContext::initialize(HINSTANCE hInstance,
                                              HINSTANCE hPrevInstance,
                                              LPSTR lpCmdLine, int nCmdShow) {
    registerApplicationContext();

    palace::WindowsApplicationContext::Parameters parameters = {
            hInstance, hPrevInstance, lpCmdLine, nCmdShow};
    m_applicationContext.initialize(parameters);
}

void palace::WindowsEngineContext::free() {
    m_applicationContext.free();
    logger().close();
}
#endif
