#ifndef ATG_PALACE_ENGINE_WINDOWS_DISPLAY_DEVICE_HPP
#define ATG_PALACE_ENGINE_WINDOWS_DISPLAY_DEVICE_HPP

#include "../display_device.hpp"

namespace palace {

class WindowsWindowServer;
class WindowsDisplayDevice : public DisplayDevice {
    PALACE_OBJECT_DATA(WindowsDisplayDevice, DisplayDevice,
                       "Display device type for Windows OSs.")

    friend WindowsWindowServer;

public:
    WindowsDisplayDevice();
    virtual ~WindowsDisplayDevice() override;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOWS_DISPLAY_DEVICE_HPP */
