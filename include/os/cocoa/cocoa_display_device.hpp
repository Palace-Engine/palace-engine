#ifndef ATG_PALACE_ENGINE_COCOA_DISPLAY_DEVICE_HPP
#define ATG_PALACE_ENGINE_COCOA_DISPLAY_DEVICE_HPP

#include "../display_device.hpp"

namespace palace {

class CocoaWindowServer;
class CocoaDisplayDevice : public DisplayDevice {
    PALACE_OBJECT_DATA(CocoaDisplayDevice, DisplayDevice,
                       "Display device type for MacOS.")

    friend CocoaWindowServer;

public:
    CocoaDisplayDevice();
    virtual ~CocoaDisplayDevice() override;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_COCOA_DISPLAY_DEVICE_HPP */
