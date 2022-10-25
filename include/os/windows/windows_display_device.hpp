#ifndef ATG_PALACE_ENGINE_WINDOWS_DISPLAY_DEVICE_HPP
#define ATG_PALACE_ENGINE_WINDOWS_DISPLAY_DEVICE_HPP

#include "../display_device.hpp"

namespace palace {

class WindowsWindowManager;
class WindowsDisplayDevice : public DisplayDevice {
    friend WindowsWindowManager;

public:
    WindowsDisplayDevice();
    virtual ~WindowsDisplayDevice() override;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOWS_DISPLAY_DEVICE_HPP */
