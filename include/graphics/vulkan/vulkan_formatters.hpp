#ifndef ATG_PALACE_ENGINE_VULKAN_FORMATTERS_HPP
#define ATG_PALACE_ENGINE_VULKAN_FORMATTERS_HPP

#include "../graphics_support.hpp"
#include "vulkan_includes.hpp"
#include "vulkan_version.hpp"

template<class CharT>
struct palace::format::formatter<palace::VulkanVersion, CharT>
    : palace::format::formatter<int, CharT> {
    template<typename FormatContext>
    auto format(const palace::VulkanVersion &v, FormatContext &ctx) {
        return format_to(ctx.out(), "[{}.{}.{}.{}]", v.variant, v.major,
                         v.minor, v.patch);
    }
};

#if PALACE_SUPPORTS_VULKAN
// VkResult Formatter
PALACE_ENUM_FORMATTER_BEGIN(, VkResult)
PALACE_ENUM_FORMATTER_ENTRY(VK_SUCCESS)
PALACE_ENUM_FORMATTER_ENTRY(VK_NOT_READY)
PALACE_ENUM_FORMATTER_ENTRY(VK_TIMEOUT)
PALACE_ENUM_FORMATTER_ENTRY(VK_EVENT_SET)
PALACE_ENUM_FORMATTER_ENTRY(VK_EVENT_RESET)
PALACE_ENUM_FORMATTER_ENTRY(VK_INCOMPLETE)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_OUT_OF_HOST_MEMORY)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_OUT_OF_DEVICE_MEMORY)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_INITIALIZATION_FAILED)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_DEVICE_LOST)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_MEMORY_MAP_FAILED)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_LAYER_NOT_PRESENT)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_EXTENSION_NOT_PRESENT)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_FEATURE_NOT_PRESENT)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_INCOMPATIBLE_DRIVER)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_TOO_MANY_OBJECTS)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_FORMAT_NOT_SUPPORTED)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_FRAGMENTED_POOL)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_UNKNOWN)
#ifdef VK_VERSION_1_1
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_OUT_OF_POOL_MEMORY)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_INVALID_EXTERNAL_HANDLE)
#endif
#ifdef VK_VERSION_1_2
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_FRAGMENTATION)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS)
#endif
#ifdef VK_VERSION_1_3
PALACE_ENUM_FORMATTER_ENTRY(VK_PIPELINE_COMPILE_REQUIRED)
#endif
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_SURFACE_LOST_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_SUBOPTIMAL_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_OUT_OF_DATE_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_VALIDATION_FAILED_EXT)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_INVALID_SHADER_NV)
#ifdef VK_ENABLE_BETA_EXTENSIONS
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR)
#endif
PALACE_ENUM_FORMATTER_ENTRY(
        VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_NOT_PERMITTED_EXT)
PALACE_ENUM_FORMATTER_ENTRY(VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT)
PALACE_ENUM_FORMATTER_ENTRY(VK_THREAD_IDLE_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_THREAD_DONE_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_OPERATION_DEFERRED_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_OPERATION_NOT_DEFERRED_KHR)
PALACE_ENUM_FORMATTER_ENTRY(VK_PIPELINE_COMPILE_REQUIRED_EXT)
PALACE_ENUM_FORMATTER_END()
#endif

#endif /* ATG_PALACE_ENGINE_VULKAN_FORMATTERS_HPP */
