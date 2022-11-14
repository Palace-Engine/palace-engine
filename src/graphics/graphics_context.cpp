#include "../../include/graphics/graphics_context.hpp"

palace::GraphicsContext::GraphicsContext(Platform platform, GraphicsApi api)
    : GraphicsApiObject(api) {
    m_platform = platform;
}

palace::GraphicsContext::~GraphicsContext() {}
