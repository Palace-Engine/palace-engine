#ifndef ATG_PALACE_ENGINE_WINDOWS_WINDOW_MANAGER_HPP
#define ATG_PALACE_ENGINE_WINDOWS_WINDOW_MANAGER_HPP

#include "../window_server.hpp"

#include "../../platform/platform_detection.hpp"
#include "../../platform/platform_includes.hpp"
#include "windows_display_device.hpp"
#include "windows_window.hpp"

namespace palace {

class WindowsApplicationContext;
class WindowsWindowServer : public WindowServer {
    friend WindowsApplicationContext;

public:
    WindowsWindowServer();
    virtual ~WindowsWindowServer();

    virtual Window *spawnWindow(const Window::Parameters &params) override;
    virtual void updateDisplayDevices() override;
    virtual void processMessages() override;

public:
    size_t findIndex(const WindowsWindow *window) const;

#if PALACE_PLATFORM_WINDOWS
    LRESULT internalWinProc(WindowsWindow *window, UINT msg, WPARAM wParam,
                            LPARAM lParam);
#endif

private:
#if PALACE_PLATFORM_WINDOWS
    bool registerWindowsClass(ATOM *windowClass);
    struct MonitorCallBackContext {
        WindowsWindowServer *windowServer;
    };

    static BOOL CALLBACK monitorCallback(HMONITOR hMonitor, HDC hdcMonitor,
                                         LPRECT lprcMonitor, LPARAM dwData);
    size_t m_windowClasses;
#endif

private:
    void setContext(WindowsApplicationContext *context) { m_context = context; }
    WindowsDisplayDevice *findDisplayDevice(const string &deviceName) const;

private:
    WindowsApplicationContext *m_context;
    ObjectContainer<Window, WindowsWindow> m_windows;
    ObjectContainer<DisplayDevice, WindowsDisplayDevice> m_displayDevices;
};

}// namespace rebar

#endif /* ATG_PALACE_ENGINE_WINDOWS_WINDOW_MANAGER_HPP */