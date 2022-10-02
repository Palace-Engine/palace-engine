#include "../../include/platform/platform_object.hpp"

palace::PlatformObject::~PlatformObject() {}

palace::PlatformObject::PlatformObject(Platform platform)
{
    m_platform = platform;
}
