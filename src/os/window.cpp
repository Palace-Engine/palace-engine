#include "../../include/os/window.hpp"

palace::Window::~Window() {}

void palace::Window::initialize(const Parameters &parameters) {
    m_parent = parameters.parent;
    m_style = parameters.style;
    m_title = parameters.title;
    m_position = parameters.position;
    m_size = parameters.size;

    m_contentSize = m_size;
    m_contentPosition = m_position;
}

void palace::Window::setFullscreen(DisplayDevice *displayDevice) {
    PALACE_LOG_INFO("Going fullscreen to display device: {} (id=@{})",
                    displayDevice->deviceName(), displayDevice->id());

    setStyle(Style::Popup);
    setPosition(displayDevice->origin());
    setSize(displayDevice->physicalSize());
}

void palace::Window::setPosition(const math::ivec2 &position) {
    PALACE_LOG_DEBUG("Position was set to: {}", position);

    updatePositionCache(position);
}

void palace::Window::setSize(const math::ivec2 &size) {
    PALACE_LOG_DEBUG("Size was set to: {}", size);

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
    PALACE_LOG_DEBUG("Updating window size cache: {} -> {}",
                     m_size, size);

    if (size != m_size) {
        // TODO: call event handler
    }

    m_size = size;
}

void palace::Window::updatePositionCache(const math::ivec2 &position) {
    PALACE_LOG_DEBUG("Updating window position cache: {} -> {}",
                     m_position, position);

    if (position != m_position) {
        // TODO: call event handler
    }

    m_position = position;
}

void palace::Window::updateContentSizeCache(const math::ivec2 &contentSize) {
    PALACE_LOG_DEBUG("Updating window content size cache: {} -> {}",
                     m_contentSize, contentSize);

    if (contentSize != m_contentSize) {
        // TODO: call event handler
    }

    m_contentSize = contentSize;
}

void palace::Window::updateContentPositionCache(
        const math::ivec2 &contentPosition) {
    PALACE_LOG_DEBUG(
            "Updating window content position cache: {} -> {}",
            m_contentPosition, contentPosition);

    if (contentPosition != m_contentPosition) {
        // TODO: call event handler
    }

    m_contentPosition = contentPosition;
}
