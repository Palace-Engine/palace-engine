#include "../../include/os/display_device.hpp"

palace::DisplayDevice::~DisplayDevice() {}

void palace::DisplayDevice::setOrigin(const math::ivec2 &origin) {
    m_origin = origin;
}

void palace::DisplayDevice::setPhysicalSize(const math::ivec2 &physicalSize) {
    m_physicalSize = physicalSize;
}

void palace::DisplayDevice::setLogicalSize(const math::ivec2 &logicalSize) {
    m_logicalSize = logicalSize;
}

void palace::DisplayDevice::setDeviceName(const string &deviceName) {
    m_deviceName = deviceName;
}

void palace::DisplayDevice::setActive(bool active) { m_active = active; }

palace::math::vec2
palace::DisplayDevice::physicalToLogical(const math::vec2 &p) const {
    return m_scaling * p;
}

palace::math::vec2
palace::DisplayDevice::logicalToPhysical(const math::vec2 &l) const {
    return l / m_scaling;
}

palace::DisplayDevice::DisplayDevice(Platform platform)
    : PlatformObject(platform) {
    m_deviceName = "";
    m_logicalSize = 0;
    m_physicalSize = 0;
    m_origin = 0;
    m_scaling = 1.0f;
    m_active = false;
}

void palace::DisplayDevice::updateScaling() {
    if (m_physicalSize.x() != 0 && m_physicalSize.y() != 0) {
        m_scaling = math::vec2(m_logicalSize) / m_physicalSize;
    }
}
