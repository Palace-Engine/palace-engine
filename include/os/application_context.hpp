#ifndef ATG_PALACE_ENGINE_APPLICATION_CONTEXT_H
#define ATG_PALACE_ENGINE_APPLICATION_CONTEXT_H

#include "../platform/platform_object.hpp"

#include "../core/dynamic_array.hpp"
#include "../graphics/graphics_context.hpp"
#include "../graphics/vulkan/vulkan_version.hpp"
#include "../types/string.hpp"
#include "window_server.hpp"

namespace palace {

class ApplicationContext : public PlatformObject {
    PALACE_OBJECT_DATA(ApplicationContext, PlatformObject,
                       "Application-level context.")

    friend EngineContext;
    using GraphicsContextContainer =
            ObjectContainer<GraphicsContext, GraphicsContext>;

public:
    struct DefaultParameters {
        int argc;
        char ***argv;
    };

protected:
    ApplicationContext(Platform platform, WindowServer *windowServer);

public:
    virtual ~ApplicationContext();

    void free();

    WindowServer *windowServer() const { return m_windowServer; }

    inline string commandLineArgument(size_t i) const;
    inline size_t commandLineArgumentCount() const;

    VulkanVersion highestSupportedVulkanVersion() const;
    virtual GraphicsContext *
    createVulkanContext(const VulkanVersion &version) = 0;

    void initialize(const DefaultParameters &params);
    void addCommandLineArgument(const string &s);
    virtual void internalFree();

protected:
    GraphicsContextContainer &graphicsContexts() { return m_graphicsContexts; }

private:
    DynamicArray<string> m_commandLineArguments;
    WindowServer *m_windowServer;
    GraphicsContextContainer m_graphicsContexts;
};

size_t ApplicationContext::commandLineArgumentCount() const {
    return m_commandLineArguments.size();
}

string ApplicationContext::commandLineArgument(size_t i) const {
    return m_commandLineArguments[i];
}

}// namespace palace

#endif /* ATG_PALACE_ENGINE_APPLICATION_CONTEXT_H */
