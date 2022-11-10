#include "../../../include/os/cocoa/cocoa_application_context.hpp"

palace::CocoaApplicationContext::CocoaApplicationContext() {}

palace::CocoaApplicationContext::~CocoaApplicationContext() {}

void palace::CocoaApplicationContext::initialize() {
    m_context = palaceCreateCocoaContext();
}

void palace::CocoaApplicationContext::free() {
    palaceFreeCocoaContext(m_context);
}
