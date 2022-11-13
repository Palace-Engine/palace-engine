#ifndef ATG_PALACE_ENGINE_WINDOWS_WINDOW_SERVER_HPP
#define ATG_PALACE_ENGINE_WINDOWS_WINDOW_SERVER_HPP

#include "../window_server.hpp"

#include "../../platform/platform_detection.hpp"
#include "../../platform/platform_includes.hpp"
#include "winapi_display_device.hpp"
#include "winapi_window.hpp"

namespace palace {

class WinApiApplicationContext;
class WinApiWindowServer : public WindowServer {
    PALACE_OBJECT_DATA(WinApiWindowServer, WindowServer,
                       "Window server for Windows OSs.")

    friend WinApiApplicationContext;

public:
    WinApiWindowServer();
    virtual ~WinApiWindowServer();

    virtual Window *spawnWindow(const Window::Parameters &params) override;
    virtual void updateDisplayDevices() override;
    virtual void processMessages() override;

public:
    size_t findIndex(const WinApiWindow *window) const;

#if PALACE_PLATFORM_WINDOWS
    LRESULT internalWinProc(WinApiWindow *window, UINT msg, WPARAM wParam,
                            LPARAM lParam);
#endif

private:
#if PALACE_PLATFORM_WINDOWS
    bool registerWindowsClass(ATOM *windowClass);
    struct MonitorCallBackContext {
        WinApiWindowServer *windowServer;
    };

    static BOOL CALLBACK monitorCallback(HMONITOR hMonitor, HDC hdcMonitor,
                                         LPRECT lprcMonitor, LPARAM dwData);
    size_t m_windowClasses;
#endif

private:
    void setContext(WinApiApplicationContext *context) { m_context = context; }
    WinApiDisplayDevice *findDisplayDevice(const string &deviceName) const;

private:
    WinApiApplicationContext *m_context;
    ObjectContainer<Window, WinApiWindow> m_windows;
    ObjectContainer<DisplayDevice, WinApiDisplayDevice> m_displayDevices;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOWS_WINDOW_SERVER_HPP */
