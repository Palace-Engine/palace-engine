#ifndef ATG_PALACE_ENGINE_WINDOW_SERVER_HPP
#define ATG_PALACE_ENGINE_WINDOW_SERVER_HPP

#include "../platform/platform_object.hpp"

#include "../core/object_container.hpp"
#include "display_device.hpp"
#include "window.hpp"

namespace palace {

class WindowServer : public PlatformObject {
    PALACE_OBJECT_DATA(WindowServer, PlatformObject,
                       "Base type for window servers which create and manage "
                       "native windows and query the OS for display devices.")

    using WindowContainer = BaseObjectContainer<Window>;
    using DisplayDeviceContainer = BaseObjectContainer<DisplayDevice>;

protected:
    WindowServer(Platform platform, WindowContainer *windows,
                 DisplayDeviceContainer *displayDevices);

public:
    virtual ~WindowServer();

    virtual void free();

    virtual Window *spawnWindow(const Window::Parameters &params = {}) = 0;
    void freeWindow(Window *&window);
    inline const WindowContainer &windows() const { return *m_windows; }
    inline const DisplayDeviceContainer &displayDevices() const {
        return *m_displayDevices;
    }

    virtual void setCursorPosition(const math::ivec2 & /* pos */) {}
    virtual void confineCursor(Window * /* window */) {
        m_cursorConfined = true;
    }
    virtual void releaseCursor() { m_cursorConfined = false; }
    bool isCursorConfined() const { return m_cursorConfined; }

    virtual void setCursorVisible(bool visible) { m_cursorVisible = visible; }
    bool isCursorVisible() const { return m_cursorVisible; };

    virtual void updateDisplayDevices() {}
    virtual void processMessages() {}

    void freeInactiveWindows();
    void freeAllWindows();

protected:
    void freeDisplayDevice(DisplayDevice *&device);
    DisplayDevice *findDisplayDevice(const string &device_name);

private:
    bool m_cursorVisible;
    bool m_cursorConfined;

protected:
    WindowContainer *m_windows;
    DisplayDeviceContainer *m_displayDevices;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOW_SERVER_HPP */
