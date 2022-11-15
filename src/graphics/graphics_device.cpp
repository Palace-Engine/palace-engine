#include "../../include/graphics/graphics_device.hpp"

palace::GraphicsDevice::GraphicsDevice(GraphicsApi api,
                                       const Containers &containers)
    : GraphicsApiObject(api) {
    m_onScreenRenderTargetContainer = containers.onScreenRenderTargetContainer;
    m_offScreenRenderTargetContainer =
            containers.offScreenRenderTargetContainer;
    m_viewportRenderTargetContainer = containers.viewportRenderTargetContainer;
}

palace::GraphicsDevice::~GraphicsDevice() {}
