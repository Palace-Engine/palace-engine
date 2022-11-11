#ifndef ATG_PALACE_ENGINE_COCOA_INTERFACE_MONITOR_H
#define ATG_PALACE_ENGINE_COCOA_INTERFACE_MONITOR_H

#include "../../display_device.hpp"

namespace palace {
namespace cocoa_interface {

struct MonitorData {
    string deviceName;
    math::ivec2 origin;
    math::ivec2 physicalSize;
    math::ivec2 logicalSize;
};

size_t monitorCount();
void monitorInformation(size_t index, MonitorData *data);

}
}

#endif /* ATG_PALACE_ENGINE_COCOA_INTERFACE_MONITOR_H */
