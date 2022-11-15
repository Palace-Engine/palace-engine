#ifndef ATG_PALACE_ENGINE_GRAPHICS_DEVICE_HPP
#define ATG_PALACE_ENGINE_GRAPHICS_DEVICE_HPP

#include "graphics_api_object.hpp"

#include "graphics_render_target.hpp"
#include "../core/object_container.hpp"

namespace palace {

class GraphicsDevice : public GraphicsApiObject {
    PALACE_OBJECT_DATA(GraphicsDevice, GraphicsApiObject,
                       "Graphics device base class.");

    using OnScreenRenderTargetContainer =
            BaseObjectContainer<OnScreenRenderTarget>;
    using OffScreenRenderTargetContainer =
            BaseObjectContainer<OffScreenRenderTarget>;
    using ViewportRenderTargetContainer =
            BaseObjectContainer<ViewportRenderTarget>;

public:
    struct Parameters {};

protected:
    struct Containers {
        OnScreenRenderTargetContainer *onScreenRenderTargetContainer;
        OffScreenRenderTargetContainer *offScreenRenderTargetContainer;
        ViewportRenderTargetContainer *viewportRenderTargetContainer;
    };

protected:
    GraphicsDevice(GraphicsApi api, const Containers &containers);

public:
    virtual ~GraphicsDevice() override;

    Result initialize(const Parameters &parameters) { return Result::Success; }

    virtual Result createOnScreenRenderTarget(
            const OnScreenRenderTarget::Parameters &parameters) = 0;
    virtual Result createOffScreenRenderTarget(
            const OffScreenRenderTarget::Parameters &parameters) = 0;
    virtual Result createViewportRenderTarget(
            const ViewportRenderTarget::Parameters &parameters) = 0;

private:
    OnScreenRenderTargetContainer *m_onScreenRenderTargetContainer;
    OffScreenRenderTargetContainer *m_offScreenRenderTargetContainer;
    ViewportRenderTargetContainer *m_viewportRenderTargetContainer;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_GRAPHICS_DEVICE_HPP */
