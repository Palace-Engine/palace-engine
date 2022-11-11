#include "../../../../include/os/cocoa/binding/cocoa_interface_monitor.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

size_t palace::cocoa_interface::monitorCount() {
    return static_cast<size_t>([[NSScreen screens] count]);
}

void palace::cocoa_interface::monitorInformation(size_t index, MonitorData *data) {
    NSScreen *screen = [NSScreen screens][index];
    data->deviceName = [[screen localizedName] UTF8String];
    data->origin = {
        static_cast<int>([screen frame].origin.x),
        static_cast<int>([screen frame].origin.y)
    };
    data->physicalSize = {
        static_cast<int>([screen frame].size.width),
        static_cast<int>([screen frame].size.height)
    };
    // Temporary.
    data->logicalSize = data->physicalSize;
}
