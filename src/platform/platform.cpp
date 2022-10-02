#include "../../include/platform/platform.hpp"

void palace::getName(Platform platform, string *target)
{
    switch (platform) {
        case Platform::Linux:
            target->assign("Linux");
            break;
        case Platform::Windows:
            target->assign("Windows");
            break;
        case Platform::Unknown:
        default:
            target->assign("unknown");
            break;
    }
}
