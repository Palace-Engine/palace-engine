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
    PALACE_LOG_INFO("Going fullscreen to display device: %s (id=@%u)",
                    displayDevice->deviceName(), displayDevice->id());

    setStyle(Style::Popup);
    setPosition(displayDevice->origin());
    setSize(displayDevice->physicalSize());
}

void palace::Window::setPosition(const math::ivec2 &position) {
    PALACE_LOG_DEBUG("Position was set to: [%d, %d]", position.x(),
                     position.y());

    updatePositionCache(position);
}

void palace::Window::setSize(const math::ivec2 &size) {
    PALACE_LOG_DEBUG("Size was set to: [%d, %d]", size.x(), size.y());

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
    PALACE_LOG_DEBUG("Updating window size cache: [%d, %d] -> [%d, %d]",
                     m_size.w(), m_size.h(), size.w(), size.h());

    if (size != m_size) {
        // TODO: call event handler
    }

    m_size = size;
}

void palace::Window::updatePositionCache(const math::ivec2 &position) {
    PALACE_LOG_DEBUG("Updating window position cache: [%d, %d] -> [%d, %d]",
                     m_position.x(), m_position.y(), position.x(),
                     position.y());

    if (position != m_position) {
        // TODO: call event handler
    }

    m_position = position;
}

void palace::Window::updateContentSizeCache(const math::ivec2 &contentSize) {
    PALACE_LOG_DEBUG("Updating window content size cache: [%d, %d] -> [%d, %d]",
                     m_contentSize.w(), m_contentSize.h(), contentSize.w(),
                     contentSize.h());

    if (contentSize != m_contentSize) {
        // TODO: call event handler
    }

    m_contentSize = contentSize;
}

void palace::Window::updateContentPositionCache(
        const math::ivec2 &contentPosition) {
    PALACE_LOG_DEBUG(
            "Updating window content position cache: [%d, %d] -> [%d, %d]",
            m_contentPosition.x(), m_contentPosition.y(), contentPosition.x(),
            contentPosition.y());

    if (contentPosition != m_contentPosition) {
        // TODO: call event handler
    }

    m_contentPosition = contentPosition;
}
