#include "../../../include/os/winapi/winapi_application_context.hpp"

#include <codecvt>
#include <locale>

#if PALACE_PLATFORM_WINDOWS
std::string utf8Encode(const std::wstring &wstr) {
    if (wstr.empty()) { return std::string(); }

    const int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &wstr[0],
                                               static_cast<int>(wstr.size()),
                                               NULL, 0, NULL, NULL);
    std::string target(static_cast<size_t>(sizeNeeded), 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()),
                        &target[0], sizeNeeded, NULL, NULL);
    return target;
}
#endif

palace::WindowsApplicationContext::WindowsApplicationContext()
    : ApplicationContext(Platform::Windows, &m_windowServer) {
    palace_assert(PALACE_PLATFORM_WINDOWS);

#if PALACE_PLATFORM_WINDOWS
    m_currentInstance = NULL;
    m_previousInstance = NULL;
    m_initialDisplayCommand = SW_HIDE;
#endif
}

palace::WindowsApplicationContext::~WindowsApplicationContext() {}

void palace::WindowsApplicationContext::initialize(const Parameters &params) {
    addObject(&m_windowServer);

    PALACE_LOG_INFO("Created window server with id=@{}", m_windowServer.id());

#if PALACE_PLATFORM_WINDOWS
    m_currentInstance = params.hInstance;
    m_previousInstance = params.hPrevInstance;
    m_initialDisplayCommand = params.nCmdShow;

    int argumentCount;
    LPWSTR *commandLineArguments =
            CommandLineToArgvW(GetCommandLineW(), &argumentCount);
    PALACE_LOG_INFO("Processing {} command line arguments", argumentCount);

    if (commandLineArguments != NULL) {
        for (int i = 0; i < argumentCount; ++i) {
            const std::wstring s = commandLineArguments[i];
            addCommandLineArgument(utf8Encode(s));
        }

        LocalFree(commandLineArguments);
    }

    m_windowServer.setContext(this);
#else
    palace::ApplicationContext::initialize(params);
#endif
}

#if PALACE_PLATFORM_WINDOWS
HINSTANCE palace::WindowsApplicationContext::currentInstance() const {
    return m_currentInstance;
}

HINSTANCE palace::WindowsApplicationContext::previousInstance() const {
    return m_previousInstance;
}

int palace::WindowsApplicationContext::initialDisplayCommand() const {
    return m_initialDisplayCommand;
}
#endif
