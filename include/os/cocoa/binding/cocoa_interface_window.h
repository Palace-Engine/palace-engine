#ifndef ATG_PALACE_ENGINE_COCOA_INTERFACE_WINDOW_H
#define ATG_PALACE_ENGINE_COCOA_INTERFACE_WINDOW_H

#include "../../window.hpp"

namespace palace {
namespace cocoa_interface {

typedef void * WindowHandle;

WindowHandle createWindow(const char *title, const math::ivec2 &position, const math::ivec2 &size, Window::Style style);
void freeWindow(WindowHandle windowHandle);

}
}

#endif /* ATG_PALACE_ENGINE_COCOA_INTERFACE_WINDOW_H */
