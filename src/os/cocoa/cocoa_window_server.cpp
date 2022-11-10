#include "../../../include/os/cocoa/cocoa_window_server.hpp"

palace::CocoaWindowServer::CocoaWindowServer()
: WindowServer(Platform::MacOS, &m_windows, &m_displayDevices) {
    m_context = nullptr;
}

palace::CocoaWindowServer::~CocoaWindowServer() {}

palace::Window *palace::CocoaWindowServer::spawnWindow(const Window::Parameters &params) {
    PALACE_LOG_INFO("Spawning new Cocoa window: [title: \"{}\", style: {}, position: \"{}\", size: {} ]", params.title, params.style, params.position, params.size);
    
    CocoaWindow *parent = (params.parent != nullptr) ? m_windows[params.parent->findId()] : nullptr;
    if (parent != nullptr) {
        PALACE_LOG_INFO("Found parent window id: @{}", parent->id());
    }
    
    CocoaWindow *newWindow = m_windows.create();
    addObject(newWindow);
    PALACE_LOG_INFO("Created new window object with id=@{}", newWindow->id());
    
    newWindow->initialize(params);
    newWindow->m_server = this;
    
    return static_cast<Window *>(newWindow);
}

void palace::CocoaWindowServer::updateDisplayDevices() {
    WindowServer::updateDisplayDevices();
}

void palace::CocoaWindowServer::processMessages() {
    
}

size_t palace::CocoaWindowServer::findIndex(const CocoaWindow *) const {
    return 0;
}

palace::CocoaDisplayDevice *palace::CocoaWindowServer::findDisplayDevice(const string &) const {
    return nullptr;
}
