#ifndef ATG_PALACE_ENGINE_GRAPHICS_API_HPP
#define ATG_PALACE_ENGINE_GRAPHICS_API_HPP

#include "../core/engine_object.hpp"

#include "../platform/platform.hpp"
#include "../types/string.hpp"

namespace palace {

enum class GraphicsApi {
    OpenGL,
    DirectX,
    Vulkan
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_GRAPHICS_API_HPP */
