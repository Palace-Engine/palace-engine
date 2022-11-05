#include "../../include/os/application_context.hpp"

palace::ApplicationContext::ApplicationContext()
    : ApplicationContext(Platform::Unknown, nullptr) {}

palace::ApplicationContext::ApplicationContext(Platform platform,
                                               WindowServer *windowServer)
    : PlatformObject(platform), m_windowServer(windowServer) {
    addObject(windowServer);
}

palace::ApplicationContext::~ApplicationContext() {}

void palace::ApplicationContext::initialize(const DefaultParameters &params) {
    for (int i = 0; i < params.argc; ++i) {
        addCommandLineArgument((*params.argv)[i]);
    }
}

void palace::ApplicationContext::addCommandLineArgument(const string &s) {
    m_commandLineArguments.append(s);
}

void palace::ApplicationContext::internalFree() {
    if (m_windowServer != nullptr) { m_windowServer->free(); }
}
