#ifndef ATG_PALACE_ENGINE_COCOA_ENGINE_CONTEXT_HPP
#define ATG_PALACE_ENGINE_COCOA_ENGINE_CONTEXT_HPP

#include "../../core/engine_context.hpp"

#include "cocoa_application_context.hpp"
#include "../../platform/platform_detection.hpp"
#include "../../platform/platform_includes.hpp"

namespace palace {

class CocoaEngineContext : public EngineContext {
public:
    CocoaEngineContext();
    virtual ~CocoaEngineContext();
    
    void initialize();
    void free();

private:
    CocoaApplicationContext m_applicationContext;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_COCOA_ENGINE_CONTEXT_HPP */
