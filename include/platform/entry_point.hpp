#ifndef ATG_PALACE_ENGINE_ENTRY_POINT_HPP
#define ATG_PALACE_ENGINE_ENTRY_POINT_HPP

#include "../os/application_context.hpp"
#include "platform_detection.hpp"

int palaceMain(rebar::ApplicationContext *context = nullptr);

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
#include <Windows.h>

#include "../os/windows/windows_application_context.hpp"

int APIENTRY WINAPI WinMain(_In_ HINSTANCE hInstance,
                            _In_opt_ HINSTANCE hPrevInstance,
                            _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    rebar::WindowsApplicationContext::Parameters parameters = {
            hInstance, hPrevInstance, lpCmdLine, nCmdShow};
    rebar::ApplicationContext::initialize<rebar::WindowsApplicationContext>(
            parameters);

    const int returnValue = rebarMain(rebar::ApplicationContext::get());
    rebar::ApplicationContext::free();

    return returnValue;
}
#endif// PALACE_PLATFORM_WINDOWS_CONSOLE_MODE
#else
int main(int argc, char *argv[]) { return rebarMain(); }
#endif

#endif// ATG_PALACE_ENGINE_ENTRY_POINT_HPP
