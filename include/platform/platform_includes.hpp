#ifndef ATG_PALACE_ENGINE_PLATFORM_INCLUDES_HPP
#define ATG_PALACE_ENGINE_PLATFORM_INCLUDES_HPP

#include "platform_detection.hpp"

#if PALACE_SUPPORTS_WINAPI
#include "disable_warnings.hpp"
#define NOMINMAX
#include <Windows.h>
#include "enable_warnings.hpp"
#endif /* PALACE_SUPPORTS_WINAPI */

#if PALACE_SUPPORTS_COCOA
#include "../os/cocoa/binding/cocoa_interface.h"
#endif /* PALACE_SUPPORTS_COCOA */

#endif /* ATG_PALACE_ENGINE_PLATFORM_INCLUDES_HPP */
