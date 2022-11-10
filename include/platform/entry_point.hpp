#ifndef ATG_PALACE_ENGINE_ENTRY_POINT_HPP
#define ATG_PALACE_ENGINE_ENTRY_POINT_HPP

#include "../logging/targets/file_log_target.hpp"
#include "../os/winapi/winapi_engine_context.hpp"
#include "platform_detection.hpp"
#include "platform_includes.hpp"

int palaceMain(palace::ApplicationContext *context = nullptr);

#if PALACE_PLATFORM_WINDOWS
#if PALACE_PLATFORM_WINDOWS_CONSOLE_MODE
int main(int argc, char *argv[]) {
    palace::ApplicationContext::DefaultParameters defaultSystemParameters = {
            argc, &argv};
    palace::ApplicationContext::initialize<palace::ApplicationContext>(
            defaultSystemParameters);

    const int returnValue = rebarMain(palace::ApplicationContext::get());
    palace::ApplicationContext::free();

    return returnValue;
}
#else
#include "../os/winapi/winapi_application_context.hpp"

int APIENTRY WINAPI WinMain(_In_ HINSTANCE hInstance,
                            _In_opt_ HINSTANCE hPrevInstance,
                            _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    palace::WindowsEngineContext context;
    palace::FileLogTarget *logTarget =
            context.logger().addTarget<palace::FileLogTarget>();
    logTarget->newFile("application_log");

    context.initialize(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    const int returnValue = palaceMain(context.applicationContext());
    context.free();

    return returnValue;
}
#endif// PALACE_PLATFORM_WINDOWS_CONSOLE_MODE
#else
int main(int argc, char *argv[]) { return palaceMain(); }
#endif

#endif// ATG_PALACE_ENGINE_ENTRY_POINT_HPP
