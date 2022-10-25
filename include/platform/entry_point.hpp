#ifndef ATG_PALACE_ENGINE_ENTRY_POINT_HPP
#define ATG_PALACE_ENGINE_ENTRY_POINT_HPP

#include "../os/application_context.hpp"
#include "platform_detection.hpp"
#include "platform_includes.hpp"

int palaceMain(palace::ApplicationContext *context = nullptr);

#if PALACE_PLATFORM_WINDOWS
#if PALACE_PLATFORM_WINDOWS_CONSOLE_MODE
int main(int argc, char *argv[])
{
    palace::ApplicationContext::DefaultParameters defaultSystemParameters = {
            argc, &argv};
    palace::ApplicationContext::initialize<palace::ApplicationContext>(
            defaultSystemParameters);

    const int returnValue = rebarMain(palace::ApplicationContext::get());
    palace::ApplicationContext::free();

    return returnValue;
}
#else
#include "../os/windows/windows_application_context.hpp"

int APIENTRY WINAPI WinMain(_In_ HINSTANCE hInstance,
                            _In_opt_ HINSTANCE hPrevInstance,
                            _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    palace::WindowsApplicationContext::Parameters parameters = {
            hInstance, hPrevInstance, lpCmdLine, nCmdShow};
    palace::WindowsApplicationContext context;
    context.initialize(parameters);

    return palaceMain(&context);
}
#endif// PALACE_PLATFORM_WINDOWS_CONSOLE_MODE
#else
int main(int argc, char *argv[]) { return palaceMain(); }
#endif

#endif// ATG_PALACE_ENGINE_ENTRY_POINT_HPP
