#ifndef ATG_PALACE_ENGINE_PLATFORM_OBJECT_HPP
#define ATG_PALACE_ENGINE_PLATFORM_OBJECT_HPP

#include "../types/string.hpp"
#include "platform.hpp"

namespace palace {

class PlatformObject
{
public:
    virtual ~PlatformObject();

    Platform platform() const { return m_platform; }
    void setName(const string &name) { m_name = name; }
    const string &name() const { return m_name; }

protected:
    PlatformObject(Platform platform);

private:
    Platform m_platform;
    string m_name;
};

}// namespace palace

#endif// ATG_PALACE_ENGINE_PLATFORM_OBJECT_HPP
