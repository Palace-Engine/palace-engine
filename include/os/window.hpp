#ifndef ATG_PALACE_ENGINE_WINDOW_H
#define ATG_PALACE_ENGINE_WINDOW_H

#include "../platform/platform_object.hpp"

#include "display_device.hpp"

namespace palace {

class WindowEventHandler;
class WindowServer;

class Window : public PlatformObject {
    PALACE_OBJECT_DATA(Window, PlatformObject,
                       "Base type for native windows.");

    friend WindowServer;

public:
    enum class State { Visible, Hidden, Maximized, Minimized, Closed, Unknown };
    enum class Style { Windowed, Popup, Unknown };

public:
    struct Parameters {
        Window *parent = nullptr;
        string title = "";
        Style style = Style::Windowed;
        math::ivec2 position = {0, 0};
        math::ivec2 size = {128, 128};
    };

public:
    virtual ~Window();

    virtual void setState(State state) { m_state = state; }
    virtual void setStyle(Style style) { m_style = style; }
    virtual void setFullscreen(DisplayDevice *displayDevice);
    virtual void setPosition(const math::ivec2 &position);
    virtual void setSize(const math::ivec2 &size);
    virtual void close() { setState(State::Closed); }

    virtual size_t findId() const = 0;

    inline math::ivec2 position() const { return m_position; }
    inline math::ivec2 size() const { return m_size; }
    inline int width() const { return m_size.w(); }
    inline int height() const { return m_size.h(); }
    inline math::ivec2 contentPosition() const { return m_contentPosition; }
    inline math::ivec2 contentSize() const { return m_contentSize; }
    inline int contentWidth() const { return m_contentSize.w(); }
    inline int contentHeight() const { return m_contentSize.h(); }
    inline Style windowStyle() const { return m_style; }
    bool isOpen() const;

protected:
    Window(Platform platform);

    virtual void initialize(const Parameters &parameters);

    void updateSizeCache(const math::ivec2 &size);
    void updatePositionCache(const math::ivec2 &position);
    void updateContentSizeCache(const math::ivec2 &contentSize);
    void updateContentPositionCache(const math::ivec2 &contentPosition);

private:
    math::ivec2 m_size;
    math::ivec2 m_position;
    math::ivec2 m_contentSize;
    math::ivec2 m_contentPosition;

    string m_title;
    State m_state;
    Style m_style;
    Window *m_parent;

protected:
    WindowEventHandler *m_eventHandler;
};

PALACE_ENUM_FORMATTER_BEGIN(palace::Window, State)
PALACE_ENUM_FORMATTER_ENTRY(Visible)
PALACE_ENUM_FORMATTER_ENTRY(Hidden)
PALACE_ENUM_FORMATTER_ENTRY(Maximized)
PALACE_ENUM_FORMATTER_ENTRY(Minimized)
PALACE_ENUM_FORMATTER_ENTRY(Closed)
PALACE_ENUM_FORMATTER_ENTRY(Unknown)
PALACE_ENUM_FORMATTER_END()

PALACE_ENUM_FORMATTER_BEGIN(palace::Window, Style)
PALACE_ENUM_FORMATTER_ENTRY(Windowed)
PALACE_ENUM_FORMATTER_ENTRY(Popup)
PALACE_ENUM_FORMATTER_ENTRY(Unknown)
PALACE_ENUM_FORMATTER_END()

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOW_H */
