#include "../../include/os/window_manager.hpp"

palace::WindowManager::WindowManager(Platform platform,
                                     ObjectList<Window> *windows,
                                     ObjectList<DisplayDevice> *displayDevices)
    : PlatformObject(platform), m_windows(windows),
      m_displayDevices(displayDevices) {
    m_cursorConfined = false;
    m_cursorVisible = true;
}

palace::WindowManager::~WindowManager() {}

void palace::WindowManager::free() {
    freeAllWindows();

    const size_t displayDeviceCount = m_displayDevices->size();
    for (size_t i = 0; i < displayDeviceCount; ++i) {
        DisplayDevice *device = (*m_displayDevices)[0];
        freeDisplayDevice(device);
    }
}

palace::Window *
palace::WindowManager::spawnWindow(const Window::Parameters & /* params */) {
    return nullptr;
}

void palace::WindowManager::freeWindow(Window *&window) {
    m_windows->free(window);
}

void palace::WindowManager::freeInactiveWindows() {
    const size_t windowCount = m_windows->size();
    for (size_t i = windowCount; i >= 1; --i) {
        Window *window = (*m_windows)[i - 1];
        if (!window->isOpen()) {
            freeWindow(window);
            ++i;
        }
    }
}

void palace::WindowManager::freeAllWindows() {
    const size_t windowCount = m_windows->size();
    for (size_t i = 0; i < windowCount; ++i) {
        Window *window = (*m_windows)[0];
        if (window->isOpen()) { window->close(); }

        freeWindow(window);
    }
}

void palace::WindowManager::freeDisplayDevice(DisplayDevice *&device) {
    m_displayDevices->free(device);
}

palace::DisplayDevice *
palace::WindowManager::findDisplayDevice(const string & /* deviceName */) {
    return nullptr;
}
