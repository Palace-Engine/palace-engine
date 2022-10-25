#include "../../include/os/window.hpp"

palace::Window::~Window() {}

void palace::Window::initialize(const Parameters &parameters) {
    m_parent = parameters.parent;
    m_style = parameters.style;
    m_title = parameters.title;
    m_position = parameters.position;
    m_size = parameters.size;
}

void palace::Window::setFullscreen(DisplayDevice *displayDevice) {
    setStyle(Style::Popup);
    setPosition(displayDevice->origin());
    setSize(displayDevice->physicalSize());
}

void palace::Window::setPosition(const math::ivec2 &position) {
    updatePositionCache(position);
}

void palace::Window::setSize(const math::ivec2 &size) {
    updateContentSizeCache(size);
}

bool palace::Window::isOpen() const { return (m_state != State::Closed); }

palace::Window::Window(Platform platform) : PlatformObject(platform) {
    m_eventHandler = nullptr;
    m_parent = nullptr;
    m_state = State::Unknown;
    m_style = Style::Unknown;
}

void palace::Window::updateSizeCache(const math::ivec2 &size) {
    if (size != m_size) {
        // TODO: call event handler
    }

    m_size = size;
}

void palace::Window::updatePositionCache(const math::ivec2 &position) {
    if (position != m_position) {
        // TODO: call event handler
    }

    m_position = position;
}

void palace::Window::updateContentSizeCache(const math::ivec2 &contentSize) {
    if (contentSize != m_contentSize) {
        // TODO: call event handler
    }

    m_contentSize = contentSize;
}

void palace::Window::updateContentPositionCache(
        const math::ivec2 &contentPosition) {
    if (contentPosition != m_contentPosition) {
        // TODO: call event handler
    }

    m_contentPosition = contentPosition;
}
