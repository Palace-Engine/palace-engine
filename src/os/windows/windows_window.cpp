#include "../../../include/os/windows/windows_window.hpp"

#include "../../../include/os/windows/windows_window_server.hpp"

palace::WindowsWindow::WindowsWindow() : Window(Platform::Windows) {
    m_server = nullptr;

#if PALACE_PLATFORM_WINDOWS
    m_handle = NULL;
#endif
}

palace::WindowsWindow::~WindowsWindow() {}

size_t palace::WindowsWindow::findId() const {
    return m_server->findIndex(this);
}

void palace::WindowsWindow::initialize(const Parameters &parameters) {
    Window::initialize(parameters);
}

void palace::WindowsWindow::setState(State state) {
    Window::setState(state);

#if PALACE_PLATFORM_WINDOWS
    if (state == State::Closed) {
        PALACE_LOG_INFO("State set to closed.");
        if (DestroyWindow(m_handle) == FALSE) {
            PALACE_LOG_ERROR("WIN32::DestroyWindow() failed.");
        }

        m_handle = NULL;
    }
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
    PALACE_LOG_INFO("Setting window position: [%d, %d]", position.x(),
                    position.y());

#if PALACE_PLATFORM_WINDOWS
    if (SetWindowPos(m_handle, NULL, position.x(), position.y(), 0, 0,
                     SWP_NOSIZE | SWP_NOZORDER) == FALSE) {
        PALACE_LOG_ERROR("WIN32::SetWindowPos() failed.");
    }
#endif
}

void palace::WindowsWindow::setSize(const math::ivec2 &size) {
    PALACE_LOG_INFO("Setting window size: [%d, %d]", size.w(), size.h());

#if PALACE_PLATFORM_WINDOWS
    if (SetWindowPos(m_handle, NULL, 0, 0, size.w(), size.h(),
                     SWP_NOMOVE | SWP_NOZORDER) == FALSE) {
        PALACE_LOG_ERROR("WIN32::SetWindowPos() failed.");
    }
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
            return window->m_server->internalWinProc(window, msg, wParam,
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
    const char *messageName = messageTypeName(msg);
    if (messageName == nullptr) {
        PALACE_LOG_TRACE_OPT("[Ignored] WIN32 message: 0x%X", msg);
    } else {
        PALACE_LOG_DEBUG("WIN32 message: %s (0x%X)", messageName, msg);
    }

    switch (msg) {
        case WM_DESTROY:
            return 0;
        case WM_QUIT:
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
    } else {
        PALACE_LOG_ERROR("WIN32::GetClientRect() failed.");
    }

    if (GetWindowRect(m_handle, &rect)) {
        updateSizeCache({rect.right - rect.left, rect.bottom - rect.top});
        updatePositionCache({rect.left, rect.top});
    } else {
        PALACE_LOG_ERROR("WIN32::GetWindowRect() failed.");
    }
}

#define MESSAGE_NAME(name)                                                     \
    case name:                                                                 \
        return #name;
constexpr const char *palace::WindowsWindow::messageTypeName(UINT msg) {
    switch (msg) {
        MESSAGE_NAME(WM_CREATE);
        MESSAGE_NAME(WM_QUIT);
        MESSAGE_NAME(WM_DESTROY);
        MESSAGE_NAME(WM_PAINT);
        MESSAGE_NAME(WM_CLOSE);
        MESSAGE_NAME(WM_SIZE);
        MESSAGE_NAME(WM_ENTERSIZEMOVE);
        MESSAGE_NAME(WM_EXITSIZEMOVE);
        MESSAGE_NAME(WM_MOVE);
        MESSAGE_NAME(WM_SETFOCUS);
        MESSAGE_NAME(WM_KILLFOCUS);
        MESSAGE_NAME(WM_KEYDOWN);
        MESSAGE_NAME(WM_INPUT);
        default:
            return nullptr;
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
