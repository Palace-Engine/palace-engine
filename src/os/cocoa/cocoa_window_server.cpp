#include "../../../include/os/cocoa/cocoa_window_server.hpp"

palace::CocoaWindowServer::CocoaWindowServer()
    : WindowServer(Platform::MacOS, &m_windows, &m_displayDevices) {
    m_context = nullptr;
}

palace::CocoaWindowServer::~CocoaWindowServer() {}

#if PALACE_SUPPORTS_COCOA
palace::Window *
palace::CocoaWindowServer::spawnWindow(const Window::Parameters &params) {
    PALACE_LOG_INFO("Spawning new Cocoa window: [title: \"{}\", style: {}, "
                    "position: \"{}\", size: {} ]",
                    params.title, params.style, params.position, params.size);

    CocoaWindow *parent = (params.parent != nullptr)
                                  ? m_windows[params.parent->findId()]
                                  : nullptr;
    if (parent != nullptr) {
        PALACE_LOG_INFO("Found parent window id: @{}", parent->id());
    }

    cocoa_interface::WindowHandle cocoaWindow = cocoa_interface::createWindow(
            params.title.c_str(), params.position, params.size, params.style);

    if (cocoaWindow == nullptr) {
        PALACE_LOG_ERROR("cocoa_interface::createWindow() failed");
        return nullptr;
    }

    CocoaWindow *newWindow = m_windows.create();
    addObject(newWindow);
    PALACE_LOG_INFO("Created new window object with id=@{}", newWindow->id());

    newWindow->initialize(params);
    newWindow->m_server = this;
    newWindow->m_window = cocoaWindow;

    return static_cast<palace::Window *>(newWindow);
}

void palace::CocoaWindowServer::updateDisplayDevices() {
    WindowServer::updateDisplayDevices();

    const size_t n = cocoa_interface::monitorCount();
    for (size_t i = 0; i < n; ++i) {
        cocoa_interface::MonitorData monitorData;
        cocoa_interface::monitorInformation(i, &monitorData);

        CocoaDisplayDevice *monitor = findDisplayDevice(monitorData.deviceName);
        if (monitor == nullptr) {
            monitor = m_displayDevices.create();
            addObject(monitor);
            monitor->setDeviceName(monitorData.deviceName);
        }

        monitor->setOrigin(monitorData.origin);
        monitor->setPhysicalSize(monitorData.physicalSize);
        monitor->setLogicalSize(monitorData.logicalSize);
    }
}

void palace::CocoaWindowServer::processMessages() {
    cocoa_interface::pollEvents();
}
#else
palace::Window *
palace::CocoaWindowServer::spawnWindow(const Window::Parameters &) {
    PALACE_LOG_ERROR("Attempting to spawn a Cocoa Window on a platform that "
                     "does not support Cocoa");
    return nullptr;
}

void palace::CocoaWindowServer::updateDisplayDevices() {
    WindowServer::updateDisplayDevices();
}

void palace::CocoaWindowServer::processMessages() {}
#endif /* PALACE_SUPPORTS_COCOA */

size_t palace::CocoaWindowServer::findIndex(const CocoaWindow *) const {
    return 0;
}

palace::CocoaDisplayDevice *
palace::CocoaWindowServer::findDisplayDevice(const string &deviceName) const {
    const size_t n = m_displayDevices.size();
    for (size_t i = 0; i < n; ++i) {
        CocoaDisplayDevice *displayDevice = m_displayDevices[i];
        if (displayDevice->deviceName() == deviceName) { return displayDevice; }
    }

    return nullptr;
}
