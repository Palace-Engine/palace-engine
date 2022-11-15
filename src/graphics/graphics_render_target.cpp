#include "../../include/graphics/graphics_render_target.hpp"

palace::RenderTarget::RenderTarget(GraphicsApi api, Type type)
    : GraphicsApiObject(api), m_type(type) {}

palace::RenderTarget::~RenderTarget() {}
