#include "../../../include/os/windows/windows_window_manager.hpp"

#include "../../../include/os/windows/windows_application_context.hpp"
#include "../../../include/os/windows/windows_display_device.hpp"

palace::WindowsWindowManager::WindowsWindowManager()
    : WindowManager(Platform::Windows, m_windows.toBase(),
                    m_displayDevices.toBase()) {
    m_context = nullptr;
}

palace::WindowsWindowManager::~WindowsWindowManager() {}

#if PALACE_PLATFORM_WINDOWS
palace::Window *
palace::WindowsWindowManager::spawnWindow(const Window::Parameters &params) {
    WindowsWindow *parent = (params.parent != nullptr)
                                    ? m_windows[params.parent->findId()]
                                    : nullptr;
    const UINT style = WindowsWindow::internalToWindowsStyle(params.style);
    HWND parentHandle = (parent != nullptr) ? parent->m_handle : NULL;
    ATOM windowsClass = registerWindowsClass();

    WindowsWindow *newWindow = m_windows.create();
    newWindow->initialize(params);
    newWindow->m_manager = this;
    newWindow->m_handle = CreateWindow(
            MAKEINTATOM(windowsClass), params.title.c_str(), style,
            params.position.x(), params.position.y(), params.size.w(),
            params.size.h(), parentHandle, NULL, m_context->currentInstance(),
            reinterpret_cast<LPVOID>(newWindow));

    SetWindowLongPtr(newWindow->m_handle, GWLP_USERDATA,
                     reinterpret_cast<LONG_PTR>(newWindow));
    SetWindowPos(newWindow->m_handle, NULL, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    newWindow->setStyle(params.style);
    newWindow->setPosition(params.position);
    newWindow->setSize(params.size);

    return static_cast<palace::Window *>(newWindow);
}

void palace::WindowsWindowManager::updateDisplayDevices() {
    WindowManager::updateDisplayDevices();
    EnumDisplayMonitors(NULL, NULL, &WindowsWindowManager::monitorCallback,
                        reinterpret_cast<LPARAM>(this));
}

void palace::WindowsWindowManager::processMessages() {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

size_t
palace::WindowsWindowManager::findIndex(const WindowsWindow *window) const {
    const size_t n = m_displayDevices.size();
    for (size_t i = 0; i < n; ++i) {
        if (m_windows[i] == window) { return i; }
    }

    return 0;
}

ATOM palace::WindowsWindowManager::registerWindowsClass() {
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
    wc.lpszClassName = "PalaceWindowClass";
    wc.hIconSm = NULL;

    return RegisterClassEx(&wc);
}

BOOL CALLBACK palace::WindowsWindowManager::monitorCallback(
        HMONITOR hMonitor, HDC /* hdcMonitor */, LPRECT lprcMonitor,
        LPARAM dwData) {
    MONITORINFOEX info;
    info.cbSize = sizeof(MONITORINFOEX);
    GetMonitorInfo(hMonitor, &info);

    WindowsWindowManager *windowManager =
            reinterpret_cast<palace::WindowsWindowManager *>(dwData);
    WindowsDisplayDevice *monitor =
            windowManager->findDisplayDevice(info.szDevice);

    if (monitor == nullptr) {
        monitor = windowManager->m_displayDevices.create();
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

LRESULT palace::WindowsWindowManager::internalWinProc(WindowsWindow *window,
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

palace::WindowsDisplayDevice *palace::WindowsWindowManager::findDisplayDevice(
        const string &deviceName) const {
    const size_t n = m_displayDevices.size();
    for (size_t i = 0; i < n; ++i) {
        WindowsDisplayDevice *displayDevice = m_displayDevices[i];
        if (displayDevice->deviceName() == deviceName) { return displayDevice; }
    }

    return nullptr;
}
