#ifndef ATG_PALACE_ENGINE_GRAPHICS_API_OBJECT_HPP
#define ATG_PALACE_ENGINE_GRAPHICS_API_OBJECT_HPP

#include "../core/engine_object.hpp"

#include "graphics_api.hpp"
#include "../platform/platform.hpp"
#include "../types/string.hpp"

namespace palace {

class GraphicsApiObject : public EngineObject {
    PALACE_OBJECT_DATA(GraphicsApiObject, EngineObject,
                       "Base object for creating graphics API objects.");

public:
    virtual ~GraphicsApiObject() override;

    inline GraphicsApi api() const { return m_api; }

protected:
    GraphicsApiObject(GraphicsApi api);

private:
    GraphicsApi m_api;
    string m_name;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_GRAPHICS_API_OBJECT_HPP */
