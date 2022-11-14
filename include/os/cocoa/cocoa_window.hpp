#ifndef ATG_PALACE_ENGINE_COCOA_WINDOW_HPP
#define ATG_PALACE_ENGINE_COCOA_WINDOW_HPP

#include "../window.hpp"

#include "../../platform/platform_includes.hpp"

namespace palace {

class CocoaWindowServer;
class CocoaWindow : public Window {
    PALACE_OBJECT_DATA(CocoaWindow, Window, "Display device type for Mac OS.");

    friend CocoaWindowServer;

public:
    CocoaWindow();
    virtual ~CocoaWindow() override;

    virtual void setState(State state) override;
    virtual void setStyle(Style style) override;
    virtual void setPosition(const math::ivec2 &position) override;
    virtual void setSize(const math::ivec2 &size) override;

    virtual size_t findId() const override;

protected:
    virtual void initialize(const Parameters &parameters) override;

private:
    CocoaWindowServer *m_server;

#if PALACE_SUPPORTS_COCOA
    cocoa_interface::WindowHandle m_window;
#endif /* PALACE_SUPPORTS_COCOA */
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_COCOA_WINDOW_HPP */
