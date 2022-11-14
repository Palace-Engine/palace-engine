#include "../../include/os/window_server.hpp"

palace::WindowServer::WindowServer(Platform platform, WindowContainer *windows,
                                   DisplayDeviceContainer *displayDevices)
    : PlatformObject(platform) {
    m_cursorConfined = false;
    m_cursorVisible = true;
    m_displayDevices = displayDevices;
    m_windows = windows;
}

palace::WindowServer::~WindowServer() {}

void palace::WindowServer::free() {
    PALACE_LOG_INFO_OPT("Freeing window server");

    freeAllWindows();

    const size_t displayDeviceCount = m_displayDevices->size();
    for (size_t i = 0; i < displayDeviceCount; ++i) {
        DisplayDevice *device = m_displayDevices->get(0);
        freeDisplayDevice(device);
    }
}

void palace::WindowServer::freeWindow(Window *&window) {
    m_windows->freeBase(window);
    window = nullptr;
}

void palace::WindowServer::freeInactiveWindows() {
    const size_t windowCount = m_windows->size();
    for (size_t i = windowCount; i >= 1; --i) {
        Window *window = m_windows->get(i - 1);
        if (!window->isOpen()) {
            freeWindow(window);
            ++i;
        }
    }
}

void palace::WindowServer::freeAllWindows() {
    const size_t windowCount = m_windows->size();
    for (size_t i = 0; i < windowCount; ++i) {
        Window *window = m_windows->get(0);
        if (window->isOpen()) { window->close(); }

        freeWindow(window);
    }
}

void palace::WindowServer::freeDisplayDevice(DisplayDevice *&device) {
    m_displayDevices->freeBase(device);
    device = nullptr;
}

palace::DisplayDevice *
palace::WindowServer::findDisplayDevice(const string & /* deviceName */) {
    return nullptr;
}
