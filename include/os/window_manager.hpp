#ifndef ATG_PALACE_ENGINE_WINDOW_MANAGER_HPP
#define ATG_PALACE_ENGINE_WINDOW_MANAGER_HPP

#include "../platform/platform_object.hpp"

#include "../core/object_container.hpp"
#include "display_device.hpp"
#include "window.hpp"

namespace palace {

class WindowManager : public PlatformObject {
protected:
    WindowManager(Platform platform, ObjectList<Window> *windows,
                  ObjectList<DisplayDevice> *displayDevices);

public:
    virtual ~WindowManager();

    virtual void free();

    virtual Window *spawnWindow(const Window::Parameters &params = {});
    void freeWindow(Window *&window);
    inline const ObjectList<Window> &windows() const { return *m_windows; }
    inline const ObjectList<DisplayDevice> &displayDevices() const {
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
    Object::ObjectList<Window> *m_windows;
    Object::ObjectList<DisplayDevice> *m_displayDevices;

    bool m_cursorVisible;
    bool m_cursorConfined;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOW_MANAGER_HPP */
