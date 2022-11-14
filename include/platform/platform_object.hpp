#ifndef ATG_PALACE_ENGINE_PLATFORM_OBJECT_HPP
#define ATG_PALACE_ENGINE_PLATFORM_OBJECT_HPP

#include "../core/engine_object.hpp"

#include "../types/string.hpp"
#include "platform.hpp"

namespace palace {

class PlatformObject : public EngineObject {
    PALACE_OBJECT_DATA(PlatformObject, EngineObject,
                       "Base type for defining objects that may have "
                       "platform-specific drivers.");

public:
    virtual ~PlatformObject();

    inline Platform platform() const { return m_platform; }
    inline void setName(const string &name) { m_name = name; }
    inline const string &name() const { return m_name; }

protected:
    PlatformObject(Platform platform);

private:
    Platform m_platform;
    string m_name;
};

}// namespace palace

#endif// ATG_PALACE_ENGINE_PLATFORM_OBJECT_HPP
