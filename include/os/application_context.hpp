#pragma once

#include "../platform/platform_object.hpp"

#include "../core/dynamic_array.hpp"
#include "../core/string.hpp"
#include "window_manager.hpp"

namespace rebar {

class ApplicationContext : public PlatformObject
{
public:
    struct DefaultParameters {
        int argc;
        char ***argv;
    };

public:
    ApplicationContext();
    virtual ~ApplicationContext();

    static ApplicationContext *get() { return s_instance; }
    WindowManager *windowManager() { return m_windowManager; }

    template<typename T_SystemContext, typename T_ContextParameters>
    static T_SystemContext *initialize(const T_ContextParameters &params);
    static void free();

    inline string commandLineArgument(size_t i) const;
    inline size_t commandLineArgumentCount() const;

protected:
    ApplicationContext(Platform platform, WindowManager *windowManager);
    void initialize(const DefaultParameters &params);
    void addCommandLineArgument(const string &s);
    virtual void internalFree();

private:
    DynamicArray<string> m_commandLineArguments;
    WindowManager *m_windowManager;

private:
    static ApplicationContext *s_instance;
};

template<typename T_SystemContext, typename T_ContextParameters>
T_SystemContext *
ApplicationContext::initialize(const T_ContextParameters &params)
{
    assert(s_instance == 0);

    T_SystemContext *newContext = Allocator::get().allocate<T_SystemContext>();
    newContext->initialize(params);
    s_instance = static_cast<ApplicationContext *>(newContext);

    return newContext;
}

size_t ApplicationContext::commandLineArgumentCount() const
{
    return m_commandLineArguments.size();
}

string ApplicationContext::commandLineArgument(size_t i) const
{
    return m_commandLineArguments[i];
}

}// namespace rebar
