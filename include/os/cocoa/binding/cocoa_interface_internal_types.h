#ifndef ATG_PALACE_ENGINE_COCOA_INTERFACE_INTERNAL_TYPES_H
#define ATG_PALACE_ENGINE_COCOA_INTERFACE_INTERNAL_TYPES_H

namespace palace {
namespace cocoa_interface {

struct Context {
    id delegate;
};

struct Window {
    id delegate;
    id window;
};

}
}

#endif /* ATG_PALACE_ENGINE_COCOA_INTERFACE_INTERNAL_TYPES_H */
