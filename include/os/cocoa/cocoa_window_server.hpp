#ifndef ATG_PALACE_ENGINE_COCOA_WINDOW_SERVER_HPP
#define ATG_PALACE_ENGINE_COCOA_WINDOW_SERVER_HPP

#include "../window_server.hpp"

#include "../../platform/platform_detection.hpp"
#include "../../platform/platform_includes.hpp"
#include "cocoa_display_device.hpp"
#include "cocoa_window.hpp"

namespace palace {

class CocoaApplicationContext;
class CocoaWindowServer : public WindowServer {
    PALACE_OBJECT_DATA(MacOsWindowServer, WindowServer,
                       "Window server for MacOS.")

    friend CocoaApplicationContext;

public:
    CocoaWindowServer();
    virtual ~CocoaWindowServer();

    virtual Window *spawnWindow(const Window::Parameters &params) override;
    virtual void updateDisplayDevices() override;
    virtual void processMessages() override;

public:
    size_t findIndex(const CocoaWindow *window) const;

private:
    void setContext(CocoaApplicationContext *context) { m_context = context; }
    CocoaDisplayDevice *findDisplayDevice(const string &deviceName) const;

private:
    CocoaApplicationContext *m_context;
    ObjectContainer<Window, CocoaWindow> m_windows;
    ObjectContainer<DisplayDevice, CocoaDisplayDevice> m_displayDevices;
};

}// namespace rebar

#endif /* ATG_PALACE_ENGINE_COCOA_WINDOW_SERVER_HPP */
