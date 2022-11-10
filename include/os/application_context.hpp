#ifndef ATG_PALACE_ENGINE_APPLICATION_CONTEXT_H
#define ATG_PALACE_ENGINE_APPLICATION_CONTEXT_H

#include "../platform/platform_object.hpp"

#include "../core/dynamic_array.hpp"
#include "../types/string.hpp"
#include "window_server.hpp"

namespace palace {

class ApplicationContext : public PlatformObject {
    PALACE_OBJECT_DATA(ApplicationContext, PlatformObject,
                       "Application-level context.")

    friend EngineContext;

public:
    struct DefaultParameters {
        int argc;
        char ***argv;
    };

public:
    ApplicationContext();
    virtual ~ApplicationContext();

    void free();

    WindowServer *windowServer() const { return m_windowServer; }

    inline string commandLineArgument(size_t i) const;
    inline size_t commandLineArgumentCount() const;

protected:
    ApplicationContext(Platform platform, WindowServer *windowServer);
    void initialize(const DefaultParameters &params);
    void addCommandLineArgument(const string &s);
    virtual void internalFree();

private:
    DynamicArray<string> m_commandLineArguments;
    WindowServer *m_windowServer;
};

size_t ApplicationContext::commandLineArgumentCount() const {
    return m_commandLineArguments.size();
}

string ApplicationContext::commandLineArgument(size_t i) const {
    return m_commandLineArguments[i];
}

}// namespace palace

#endif /* ATG_PALACE_ENGINE_APPLICATION_CONTEXT_H */
