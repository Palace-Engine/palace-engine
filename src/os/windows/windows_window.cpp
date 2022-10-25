#include "../../../include/os/windows/windows_window.hpp"

#include "../../../include/os/windows/windows_window_manager.hpp"

palace::WindowsWindow::WindowsWindow() : Window(Platform::Windows) {
    m_manager = nullptr;

#if PALACE_PLATFORM_WINDOWS
    m_handle = NULL;
#endif
}

palace::WindowsWindow::~WindowsWindow() {}

size_t palace::WindowsWindow::findId() const {
    return m_manager->findIndex(this);
}

void palace::WindowsWindow::setState(State state) {
    Window::setState(state);

#if PALACE_PLATFORM_WINDOWS

#endif
}

void palace::WindowsWindow::setStyle(Style style) {
    switch (style) {
        case Style::Popup:
            setStylePopup();
            break;
        case Style::Windowed:
            setStyleWindowed();
            break;
        case Style::Unknown:
            break;
    }
}

void palace::WindowsWindow::setPosition(const math::ivec2 &position) {
#if PALACE_PLATFORM_WINDOWS
    SetWindowPos(m_handle, NULL, position.x(), position.y(), 0, 0,
                 SWP_NOSIZE | SWP_NOZORDER);
#endif
}

void palace::WindowsWindow::setSize(const math::ivec2 &size) {
#if PALACE_PLATFORM_WINDOWS
    SetWindowPos(m_handle, NULL, 0, 0, size.w(), size.h(),
                 SWP_NOMOVE | SWP_NOZORDER);
#endif
}

#if PALACE_PLATFORM_WINDOWS
UINT palace::WindowsWindow::internalToWindowsStyle(Style style) {
    switch (style) {
        case Style::Windowed:
            return WS_OVERLAPPEDWINDOW | WS_VISIBLE;
        case Style::Popup:
            return WS_POPUP | WS_VISIBLE;
        case Style::Unknown:
            return WS_OVERLAPPED;
    }

    return WS_OVERLAPPED;
}

LRESULT WINAPI palace::WindowsWindow::WinProc(HWND hWnd, UINT msg,
                                              WPARAM wParam, LPARAM lParam) {
    const LONG_PTR userData = GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch (msg) {
        case WM_CREATE: {
            WindowsWindow *window = reinterpret_cast<WindowsWindow *>(lParam);
            return window->m_manager->internalWinProc(window, msg, wParam,
                                                      lParam);
        }
    }

    WindowsWindow *window = reinterpret_cast<WindowsWindow *>(userData);
    if (window != nullptr) {
        return window->internalWinProc(msg, wParam, lParam);
    } else {
        // TODO: error on unhandled message
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

LRESULT palace::WindowsWindow::internalWinProc(UINT msg, WPARAM wParam,
                                               LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(m_handle, &ps);
            return 0;
        }
        case WM_CLOSE:
            setState(State::Closed);
            return 0;
        case WM_SIZE:
            updatePositionAndSize();
            return 0;
        case WM_ENTERSIZEMOVE:
            updatePositionAndSize();
            return 0;
        case WM_EXITSIZEMOVE:
            updatePositionAndSize();
            return 0;
        case WM_MOVE:
            updatePositionAndSize();
            return 0;
        case WM_SETFOCUS:
            // TODO
            return 0;
        case WM_KILLFOCUS:
            // TODO
            return 0;
        case WM_KEYDOWN:
            // TODO
            return 0;
        case WM_INPUT:
            // TODO
            return 0;
    }

    return DefWindowProc(m_handle, msg, wParam, lParam);
}

void palace::WindowsWindow::updatePositionAndSize() {
    RECT rect;
    if (GetClientRect(m_handle, &rect)) {
        updateContentSizeCache(
                {rect.right - rect.left, rect.bottom - rect.top});
        updateContentPositionCache({rect.left, rect.top});
    }

    if (GetWindowRect(m_handle, &rect)) {
        updateSizeCache({rect.right - rect.left, rect.bottom - rect.top});
        updatePositionCache({rect.left, rect.top});
    }
}
#endif

void palace::WindowsWindow::setStyleWindowed() {
    Window::setStyle(Style::Windowed);

#if PALACE_PLATFORM_WINDOWS
    SetWindowLongPtr(m_handle, GWL_STYLE,
                     internalToWindowsStyle(Style::Windowed));
    SetWindowPos(m_handle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED);
    ShowWindow(m_handle, SW_SHOW);
    SetForegroundWindow(m_handle);
#endif
}

void palace::WindowsWindow::setStylePopup() {
    Window::setStyle(Style::Popup);

#if PALACE_PLATFORM_WINDOWS
    SetWindowLongPtr(m_handle, GWL_STYLE, internalToWindowsStyle(Style::Popup));
    SetWindowPos(m_handle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED);
    ShowWindow(m_handle, SW_SHOW);
    SetForegroundWindow(m_handle);
#endif
}
