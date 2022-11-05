#include "../../../include/os/windows/windows_window_server.hpp"

#include "../../../include/os/windows/windows_application_context.hpp"
#include "../../../include/os/windows/windows_display_device.hpp"

palace::WindowsWindowServer::WindowsWindowServer()
    : WindowServer(Platform::Windows, &m_windows, &m_displayDevices) {
    m_context = nullptr;

#if PALACE_PLATFORM_WINDOWS
    m_windowClasses = 0;
#endif
}

palace::WindowsWindowServer::~WindowsWindowServer() {}

#if PALACE_PLATFORM_WINDOWS
palace::Window *
palace::WindowsWindowServer::spawnWindow(const Window::Parameters &params) {
    PALACE_LOG_INFO("Spawning new window: [ title: \"%s\", style: %d, position: "
                    "[%d, %d], size: [%d, %d] ]",
                    params.title.c_str(),
                    static_cast<unsigned int>(params.style),
                    params.position.x(), params.position.y(), params.size.w(),
                    params.size.h());

    WindowsWindow *parent = (params.parent != nullptr)
                                    ? m_windows[params.parent->findId()]
                                    : nullptr;
    const UINT style = WindowsWindow::internalToWindowsStyle(params.style);
    HWND parentHandle = (parent != nullptr) ? parent->m_handle : NULL;
    ATOM windowClass;
    if (!registerWindowsClass(&windowClass)) {
        PALACE_LOG_ERROR("Window class registration failed.");
        return nullptr;
    }

    WindowsWindow *newWindow = m_windows.create();
    addObject(newWindow);
    PALACE_LOG_INFO("Created new window object with id=@%u", newWindow->id());

    HWND newWindowHandle;
    newWindowHandle = CreateWindow(
            MAKEINTATOM(windowClass), params.title.c_str(), style,
            params.position.x(), params.position.y(), params.size.w(),
            params.size.h(), parentHandle, NULL, m_context->currentInstance(),
            reinterpret_cast<LPVOID>(newWindow));

    if (newWindowHandle == NULL) {
        PALACE_LOG_ERROR("WIN32::CreateWindow() returned NULL.");
        goto failed;
    }

    newWindow->initialize(params);
    newWindow->m_server = this;
    newWindow->m_handle = newWindowHandle;

    SetLastError(0);
    SetWindowLongPtr(newWindow->m_handle, GWLP_USERDATA,
                     reinterpret_cast<LONG_PTR>(newWindow));
    if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) {
        PALACE_LOG_ERROR("WIN32::SetWindowLongPtr() failed.");
        goto failed;
    }

    if (SetWindowPos(newWindow->m_handle, NULL, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                             SWP_FRAMECHANGED) == FALSE) {
        PALACE_LOG_ERROR("WIN32::SetWindowPos() failed.");
        goto failed;
    }

    newWindow->setStyle(params.style);
    newWindow->setPosition(params.position);
    newWindow->setSize(params.size);

    return static_cast<palace::Window *>(newWindow);

failed:
    m_windows.free(newWindow);
    return nullptr;
}

void palace::WindowsWindowServer::updateDisplayDevices() {
    WindowServer::updateDisplayDevices();
    EnumDisplayMonitors(NULL, NULL, &WindowsWindowServer::monitorCallback,
                        reinterpret_cast<LPARAM>(this));
}

void palace::WindowsWindowServer::processMessages() {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

size_t
palace::WindowsWindowServer::findIndex(const WindowsWindow *window) const {
    return m_windows.findFirst(window);
}

bool palace::WindowsWindowServer::registerWindowsClass(ATOM *windowClass) {
    const std::string windowClassName =
            "PalaceWindowClass_" + std::to_string(m_windowClasses++);

    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowsWindow::WinProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_context->currentInstance();
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = windowClassName.c_str();
    wc.hIconSm = NULL;

    const ATOM newWindowClass = RegisterClassEx(&wc);
    if (newWindowClass == 0) {
        return false;
    } else {
        *windowClass = newWindowClass;
        return true;
    }
}

BOOL CALLBACK palace::WindowsWindowServer::monitorCallback(HMONITOR hMonitor,
                                                           HDC /* hdcMonitor */,
                                                           LPRECT lprcMonitor,
                                                           LPARAM dwData) {
    MONITORINFOEX info;
    info.cbSize = sizeof(MONITORINFOEX);
    GetMonitorInfo(hMonitor, &info);

    WindowsWindowServer *windowServer =
            reinterpret_cast<palace::WindowsWindowServer *>(dwData);
    WindowsDisplayDevice *monitor =
            windowServer->findDisplayDevice(info.szDevice);

    if (monitor == nullptr) {
        monitor = windowServer->m_displayDevices.create();
        windowServer->addObject(monitor);
        monitor->setDeviceName(info.szDevice);
    }

    DEVMODE devMode;
    devMode.dmSize = sizeof(devMode);
    devMode.dmDriverExtra = 0;
    EnumDisplaySettings(info.szDevice, ENUM_CURRENT_SETTINGS, &devMode);

    monitor->setOrigin({lprcMonitor->left, lprcMonitor->top});
    monitor->setPhysicalSize(
            {int(devMode.dmPelsWidth), int(devMode.dmPelsHeight)});
    monitor->setLogicalSize({int(lprcMonitor->right - lprcMonitor->left),
                             int(lprcMonitor->bottom - lprcMonitor->top)});

    return TRUE;
}

LRESULT palace::WindowsWindowServer::internalWinProc(WindowsWindow *window,
                                                     UINT msg, WPARAM wParam,
                                                     LPARAM lParam) {
    return DefWindowProc(window->m_handle, msg, wParam, lParam);
}
#else
palace::Window *
palace::WindowsWindowManager::spawnWindow(const Window::Parameters &) {
    return nullptr;
}

void palace::WindowsWindowManager::updateDisplayDevices() {}
void palace::WindowsWindowManager::processMessages() {}
#endif

palace::WindowsDisplayDevice *
palace::WindowsWindowServer::findDisplayDevice(const string &deviceName) const {
    const size_t n = m_displayDevices.size();
    for (size_t i = 0; i < n; ++i) {
        WindowsDisplayDevice *displayDevice = m_displayDevices[i];
        if (displayDevice->deviceName() == deviceName) { return displayDevice; }
    }

    return nullptr;
}
