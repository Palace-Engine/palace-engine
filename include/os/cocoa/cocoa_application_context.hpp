#ifndef ATG_PALACE_ENGINE_COCOA_APPLICATION_CONTEXT_HPP
#define ATG_PALACE_ENGINE_COCOA_APPLICATION_CONTEXT_HPP

#include "../application_context.hpp"

#include "../../platform/platform_detection.hpp"
#include "../../platform/platform_includes.hpp"
#include "cocoa_window_server.hpp"
#include "binding/cocoa_interface.h"

namespace palace {

class CocoaEngineContext;
class CocoaApplicationContext : public ApplicationContext {
    PALACE_OBJECT_DATA(CocoaApplicationContext, ApplicationContext,
                       "Application-level context for MacOS applications.")
    
    friend CocoaEngineContext;
    
public:
    CocoaApplicationContext();
    virtual ~CocoaApplicationContext();
    
    void initialize();
    void free();
    
private:
    CocoaWindowServer m_windowServer;
    PalaceCocoaContextHandle m_context;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_COCOA_APPLICATION_CONTEXT_HPP */