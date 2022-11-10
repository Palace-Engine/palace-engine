#include "../../../include/os/cocoa/cocoa_window.hpp"

palace::CocoaWindow::CocoaWindow() : Window(Platform::MacOS) {
    m_server = nullptr;
}

palace::CocoaWindow::~CocoaWindow() {
    
}

void palace::CocoaWindow::setState(State state) {
    Window::setState(state);
}

void palace::CocoaWindow::setStyle(Style style) {
    Window::setStyle(style);
}

void palace::CocoaWindow::setPosition(const math::ivec2 &position) {
    Window::setPosition(position);
}

void palace::CocoaWindow::setSize(const math::ivec2 &size) {
    Window::setSize(size);
}

size_t palace::CocoaWindow::findId() const {
    return 0;
}

void palace::CocoaWindow::initialize(const Parameters &) {
    
}
