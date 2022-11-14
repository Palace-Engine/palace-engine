#ifndef ATG_PALACE_ENGINE_VULKAN_INCLUDES_HPP
#define ATG_PALACE_ENGINE_VULKAN_INCLUDES_HPP

#include "../../platform/platform_detection.hpp"
#include "../graphics_support.hpp"

#include "../../platform/platform_includes.hpp"

#if PALACE_SUPPORTS_VULKAN
#include <vulkan/vulkan_core.h>

#if PALACE_SUPPORTS_WINAPI
#include <vulkan/vulkan_win32.h>
#endif

#endif

#endif /* ATG_PALACE_ENGINE_VULKAN_INCLUDES_HPP */
