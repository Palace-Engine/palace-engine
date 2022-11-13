#include "../../../include/os/winapi/winapi_engine_context.hpp"

palace::WinApiEngineContext::WinApiEngineContext()
    : EngineContext(&m_applicationContext) {}

palace::WinApiEngineContext::~WinApiEngineContext() {}

#if PALACE_PLATFORM_WINDOWS
void palace::WinApiEngineContext::initialize(HINSTANCE hInstance,
                                              HINSTANCE hPrevInstance,
                                              LPSTR lpCmdLine, int nCmdShow) {
    registerApplicationContext();

    palace::WinApiApplicationContext::Parameters parameters = {
            hInstance, hPrevInstance, lpCmdLine, nCmdShow};
    m_applicationContext.initialize(parameters);
}

void palace::WinApiEngineContext::free() {
    m_applicationContext.free();
    logger().close();
}
#endif
