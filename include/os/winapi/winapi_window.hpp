#ifndef ATG_PALACE_ENGINE_WINDOWS_WINDOW_HPP
#define ATG_PALACE_ENGINE_WINDOWS_WINDOW_HPP

#include "../window.hpp"

#include "../../platform/platform_includes.hpp"

namespace palace {

class WinApiWindowServer;

class WinApiWindow : public Window {
    PALACE_OBJECT_DATA(WinApiWindow, Window,
                       "Display device type for Windows OSs.")

    friend WinApiWindowServer;

public:
    WinApiWindow();
    virtual ~WinApiWindow() override;

    virtual void setState(State state) override;
    virtual void setStyle(Style style) override;
    virtual void setPosition(const math::ivec2 &position) override;
    virtual void setSize(const math::ivec2 &size) override;

    virtual size_t findId() const override;

protected:
    virtual void initialize(const Parameters &parameters) override;

private:
#if PALACE_PLATFORM_WINDOWS
    static UINT internalToWindowsStyle(Window::Style style);
    static LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam,
                                  LPARAM lParam);
    LRESULT internalWinProc(UINT msg, WPARAM wParam, LPARAM lParam);
    void updatePositionAndSize();

    static constexpr const char *messageTypeName(UINT msg);
#endif

    void setStyleWindowed();
    void setStylePopup();

private:
    WinApiWindowServer *m_server;

#if PALACE_PLATFORM_WINDOWS
    HWND m_handle;
#endif
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOWS_WINDOW_HPP */
