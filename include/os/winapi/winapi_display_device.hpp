#ifndef ATG_PALACE_ENGINE_WINDOWS_DISPLAY_DEVICE_HPP
#define ATG_PALACE_ENGINE_WINDOWS_DISPLAY_DEVICE_HPP

#include "../display_device.hpp"

namespace palace {

class WinApiWindowServer;
class WinApiDisplayDevice : public DisplayDevice {
    PALACE_OBJECT_DATA(WinApiDisplayDevice, DisplayDevice,
                       "Display device type for Windows OSs.")

    friend WinApiWindowServer;

public:
    WinApiDisplayDevice();
    virtual ~WinApiDisplayDevice() override;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_WINDOWS_DISPLAY_DEVICE_HPP */
