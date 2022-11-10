#ifndef ATG_PALACE_ENGINE_COCOA_INTERFACE_CONTEXT_H
#define ATG_PALACE_ENGINE_COCOA_INTERFACE_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void * PalaceCocoaContextHandle;

PalaceCocoaContextHandle palaceCreateCocoaContext(void);
void palaceFreeCocoaContext(PalaceCocoaContextHandle context);

#ifdef __cplusplus
}
#endif

#endif /* ATG_PALACE_ENGINE_COCOA_INTERFACE_CONTEXT_H */
