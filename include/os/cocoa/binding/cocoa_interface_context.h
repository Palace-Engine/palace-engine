#ifndef ATG_PALACE_ENGINE_COCOA_INTERFACE_CONTEXT_H
#define ATG_PALACE_ENGINE_COCOA_INTERFACE_CONTEXT_H

namespace palace {
namespace cocoa_interface {

typedef void * ContextHandle;

ContextHandle createContext(void);
void freeContext(ContextHandle context);
void pollEvents(void);

}
}

#endif /* ATG_PALACE_ENGINE_COCOA_INTERFACE_CONTEXT_H */
