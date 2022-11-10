#ifndef ATG_PALACE_ENGINE_DISPLAY_DEVICE_H
#define ATG_PALACE_ENGINE_DISPLAY_DEVICE_H

#include "../platform/platform_object.hpp"

#include "../math/math.hpp"
#include "../types/string.hpp"

namespace palace {

class WindowServer;
class DisplayDevice : public PlatformObject {
    PALACE_OBJECT_DATA(DisplayDevice, PlatformObject,
                       "Base type for display devices like monitors.")

    friend WindowServer;

public:
    struct Parameters {
        string device_name;
        math::ivec2 origin;
        math::ivec2 physical_size;
        math::ivec2 logical_size;
    };

public:
    virtual ~DisplayDevice();

    math::ivec2 origin() const { return m_origin; }
    math::ivec2 physicalSize() const { return m_physicalSize; }
    math::ivec2 logicalSize() const { return m_logicalSize; }
    math::vec2 scaling() const { return m_scaling; }

    math::vec2 physicalToLogical(const math::vec2 &p) const;
    math::vec2 logicalToPhysical(const math::vec2 &l) const;

    const string &deviceName() const { return m_deviceName; }

protected:
    DisplayDevice(Platform platform);

    void setOrigin(const math::ivec2 &origin);
    void setPhysicalSize(const math::ivec2 &physicalSize);
    void setLogicalSize(const math::ivec2 &logicalSize);
    void setDeviceName(const string &deviceName);

    void setActive(bool active);
    void updateScaling();

private:
    string m_deviceName;
    bool m_active;

    math::ivec2 m_origin;
    math::ivec2 m_physicalSize;
    math::ivec2 m_logicalSize;
    math::vec2 m_scaling;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_DISPLAY_DEVICE_H */
