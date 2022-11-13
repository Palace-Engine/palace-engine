#include "../../../include/os/winapi/winapi_window.hpp"

#include "../../../include/os/winapi/winapi_window_server.hpp"

palace::WinApiWindow::WinApiWindow() : Window(Platform::Windows) {
    m_server = nullptr;

#if PALACE_PLATFORM_WINDOWS
    m_handle = NULL;
#endif
}

palace::WinApiWindow::~WinApiWindow() {}

size_t palace::WinApiWindow::findId() const {
    return m_server->findIndex(this);
}

void palace::WinApiWindow::initialize(const Parameters &parameters) {
    Window::initialize(parameters);
}

void palace::WinApiWindow::setState(State state) {
    Window::setState(state);

    PALACE_LOG_INFO("State set to {}", state);

#if PALACE_PLATFORM_WINDOWS
    if (state == State::Closed) {
        if (DestroyWindow(m_handle) == FALSE) {
            PALACE_LOG_ERROR("WIN32::DestroyWindow() failed.");
        }

        m_handle = NULL;
    }
#endif
}

void palace::WinApiWindow::setStyle(Style style) {
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

void palace::WinApiWindow::setPosition(const math::ivec2 &position) {
    PALACE_LOG_INFO("Setting window position:{}", position);

#if PALACE_PLATFORM_WINDOWS
    if (SetWindowPos(m_handle, NULL, position.x(), position.y(), 0, 0,
                     SWP_NOSIZE | SWP_NOZORDER) == FALSE) {
        PALACE_LOG_ERROR("WIN32::SetWindowPos() failed.");
    }
#endif
}

void palace::WinApiWindow::setSize(const math::ivec2 &size) {
    PALACE_LOG_INFO("Setting window size: {}", size);

#if PALACE_PLATFORM_WINDOWS
    if (SetWindowPos(m_handle, NULL, 0, 0, size.w(), size.h(),
                     SWP_NOMOVE | SWP_NOZORDER) == FALSE) {
        PALACE_LOG_ERROR("WIN32::SetWindowPos() failed.");
    }
#endif
}

#if PALACE_PLATFORM_WINDOWS
UINT palace::WinApiWindow::internalToWindowsStyle(Style style) {
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

LRESULT WINAPI palace::WinApiWindow::WinProc(HWND hWnd, UINT msg,
                                              WPARAM wParam, LPARAM lParam) {
    const LONG_PTR userData = GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch (msg) {
        case WM_CREATE: {
            WinApiWindow *window = reinterpret_cast<WinApiWindow *>(lParam);
            return window->m_server->internalWinProc(window, msg, wParam,
                                                     lParam);
        }
    }

    WinApiWindow *window = reinterpret_cast<WinApiWindow *>(userData);
    if (window != nullptr) {
        return window->internalWinProc(msg, wParam, lParam);
    } else {
        // TODO: error on unhandled message
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

LRESULT palace::WinApiWindow::internalWinProc(UINT msg, WPARAM wParam,
                                               LPARAM lParam) {
    const char *messageName = messageTypeName(msg);
    if (messageName == nullptr) {
        PALACE_LOG_TRACE_OPT("[Ignored] WIN32 message: {:#x}", msg);
    } else {
        PALACE_LOG_DEBUG("WIN32 message: {} ({:#x})", messageName, msg);
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

void palace::WinApiWindow::updatePositionAndSize() {
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
constexpr const char *palace::WinApiWindow::messageTypeName(UINT msg) {
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

void palace::WinApiWindow::setStyleWindowed() {
    Window::setStyle(Style::Windowed);

#if PALACE_PLATFORM_WINDOWS
    SetWindowLongPtr(m_handle, GWL_STYLE,
                     internalToWindowsStyle(Style::Windowed));
    SetWindowPos(m_handle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED);
    ShowWindow(m_handle, SW_SHOW);
    SetForegroundWindow(m_handle);
#endif
}

void palace::WinApiWindow::setStylePopup() {
    Window::setStyle(Style::Popup);

#if PALACE_PLATFORM_WINDOWS
    SetWindowLongPtr(m_handle, GWL_STYLE, internalToWindowsStyle(Style::Popup));
    SetWindowPos(m_handle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED);
    ShowWindow(m_handle, SW_SHOW);
    SetForegroundWindow(m_handle);
#endif
}
