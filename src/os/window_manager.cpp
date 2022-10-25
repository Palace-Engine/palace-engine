#include "../../include/os/window_manager.hpp"

palace::WindowManager::WindowManager(
        Platform platform, BaseObjectContainer<Window> *windows,
        BaseObjectContainer<DisplayDevice> *displayDevices)
    : PlatformObject(platform), m_windows(windows),
      m_displayDevices(displayDevices) {
    m_cursorConfined = false;
    m_cursorVisible = true;
}

palace::WindowManager::~WindowManager() {}

void palace::WindowManager::free() {
    freeAllWindows();

    const size_t displayDeviceCount = this->displayDeviceCount();
    for (size_t i = 0; i < displayDeviceCount; ++i) { freeDisplayDevice(0); }
}

palace::Window *
palace::WindowManager::spawnWindow(const Window::Parameters & /* params */) {
    return nullptr;
}

void palace::WindowManager::freeWindow(Window *window) {
    m_windows->free(window->findId());
}

palace::DisplayDevice *
palace::WindowManager::getDisplayDevice(size_t index) const {
    return (*m_displayDevices)[index];
}

size_t palace::WindowManager::displayDeviceCount() const {
    return m_displayDevices->size();
}

void palace::WindowManager::freeInactiveWindows() {
    const size_t windowCount = this->windowCount();
    for (size_t i = windowCount; i >= 1; --i) {
        Window *window = (*m_windows)[i - 1];
        if (!window->isOpen()) {
            freeWindow(window);
            ++i;
        }
    }
}

void palace::WindowManager::freeAllWindows() {
    const size_t windowCount = this->windowCount();
    for (size_t i = 0; i < windowCount; ++i) {
        Window *window = (*m_windows)[0];
        if (window->isOpen()) { window->close(); }

        freeWindow(window);
    }
}

void palace::WindowManager::freeDisplayDevice(size_t index) {
    m_displayDevices->free(index);
}

palace::DisplayDevice *
palace::WindowManager::findDisplayDevice(const string & /* deviceName */) {
    return nullptr;
}
