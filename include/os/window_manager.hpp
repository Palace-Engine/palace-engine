#ifndef ATG_PALACE_ENGINE_WINDOW_MANAGER_HPP
#define ATG_PALACE_ENGINE_WINDOW_MANAGER_HPP

#include "../platform/platform_object.hpp"

#include "../core/object_container.hpp"
#include "display_device.hpp"
#include "window.hpp"

namespace palace {

class WindowManager : PlatformObject {
protected:
    WindowManager(Platform platform, BaseObjectContainer<Window> *windows,
                  BaseObjectContainer<DisplayDevice> *displayDevices);

public:
    virtual ~WindowManager();

    virtual void free();

    virtual Window *spawnWindow(const Window::Parameters &params = {});
    size_t windowCount() const { return m_windows->size(); }
    Window *getWindow(size_t index) { return (*m_windows)[index]; }
    void freeWindow(Window *window);

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

    DisplayDevice *getDisplayDevice(size_t index) const;
    size_t displayDeviceCount() const;

    void freeInactiveWindows();
    void freeAllWindows();

protected:
    void freeDisplayDevice(size_t index);
    DisplayDevice *findDisplayDevice(const string &device_name);

private:
    BaseObjectContainer<Window> *m_windows;
    BaseObjectContainer<DisplayDevice> *m_displayDevices;

    bool m_cursorVisible;
    bool m_cursorConfined;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOW_MANAGER_HPP */
