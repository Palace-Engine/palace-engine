#ifndef ATG_PALACE_ENGINE_GRAPHICS_RENDER_TARGET_HPP
#define ATG_PALACE_ENGINE_GRAPHICS_RENDER_TARGET_HPP

#include "graphics_api_object.hpp"

#include "../math/math.hpp"

namespace palace {

class RenderTarget : public GraphicsApiObject {
public:
    enum class Type { OnScreen, OffScreen, Viewport };

protected:
    RenderTarget(GraphicsApi api, Type type);

public:
    virtual ~RenderTarget();

    virtual Result setSize(const math::ivec2 &size) = 0;
    virtual Result setOrigin(const math::ivec2 &size) = 0;
    virtual math::ivec2 size() = 0;
    virtual math::ivec2 origin() = 0;
    virtual Result use() = 0;
    inline Type type() const { return m_type; }

private:
    Type m_type;
};

class OnScreenRenderTarget : public RenderTarget {
public:
    struct Parameters {};

public:
    OnScreenRenderTarget(GraphicsApi api) : RenderTarget(api, Type::OnScreen) {}
    virtual ~OnScreenRenderTarget() {}
};

class OffScreenRenderTarget : public RenderTarget {
public:
    struct Parameters {};

public:
    OffScreenRenderTarget(GraphicsApi api)
        : RenderTarget(api, Type::OffScreen) {}
    virtual ~OffScreenRenderTarget() {}
};

class ViewportRenderTarget : public RenderTarget {
public:
    struct Parameters {};

public:
    ViewportRenderTarget(GraphicsApi api) : RenderTarget(api, Type::Viewport) {}
    virtual ~ViewportRenderTarget() {}
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_GRAPHICS_RENDER_TARGET_HPP */
