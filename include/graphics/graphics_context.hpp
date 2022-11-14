#ifndef ATG_PALACE_ENGINE_GRAPHICS_CONTEXT_HPP
#define ATG_PALACE_ENGINE_GRAPHICS_CONTEXT_HPP

#include "graphics_api_object.hpp"

#include "../platform/platform.hpp"
#include "../types/string.hpp"

namespace palace {

class GraphicsContext : public GraphicsApiObject {
    PALACE_OBJECT_DATA(GraphicsContext, GraphicsApiObject,
                       "Top level graphics API context.")
public:
    struct Parameters {};

public:
    virtual ~GraphicsContext() override;

    inline Platform platform() const { return m_platform; }

    Result initialize(const Parameters &parameters) { return Result::Success; }

    virtual void queryDevices() = 0;
    virtual size_t deviceCount() = 0;
    virtual string deviceName(size_t i) = 0;

protected:
    GraphicsContext(Platform platform, GraphicsApi api);

private:
    Platform m_platform;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_GRAPHICS_CONTEXT_HPP */
