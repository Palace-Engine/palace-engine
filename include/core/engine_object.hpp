#ifndef ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP
#define ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP

#include "engine_context.hpp"

#include <sstream>

namespace palace {

#define PALACE_ENGINE_LOG_LEVEL PALACE_ENGINE_LOG_LEVEL_DEBUG

/*
#define OBJECT_LOG_FUNCTION(name, level)                                       \
    template<typename... Args>                                                 \
    void name(std::string_view format, std::string_view objectName,            \
              std::string_view function, int line, Args... args) {             \
        std::stringstream ss;                                                  \
        ss << objectName << "("                                                \
           << "id=@" << id() << ")::" << function << "::L" << line << " | "    \
           << format;                                                          \
        logger().name(ss.str(), args...);                                      \
    }
    */

#define PALACE_OBJECT_LOG(level, format_string, ...)                           \
    {                                                                          \
        const std::string formatted = palace::format::format(                  \
                "{}(id=@{})::{}::L{} | " format_string, s_objectName,          \
                this->id(), __func__, __LINE__ __VA_OPT__(, ) __VA_ARGS__);    \
        logger().level(formatted);                                             \
    }

#define PALACE_LOG_FATAL(format, ...)                                          \
    PALACE_OBJECT_LOG(fatal, format __VA_OPT__(, ) __VA_ARGS__)
#define PALACE_LOG_ERROR(format, ...)                                          \
    PALACE_OBJECT_LOG(error, format __VA_OPT__(, ) __VA_ARGS__)
#define PALACE_LOG_WARNING(format, ...)                                        \
    PALACE_OBJECT_LOG(warning, format __VA_OPT__(, ) __VA_ARGS__)
#define PALACE_LOG_INFO(format, ...)                                           \
    PALACE_OBJECT_LOG(info, format __VA_OPT__(, ) __VA_ARGS__)
#define PALACE_LOG_DEBUG(format, ...)                                          \
    PALACE_OBJECT_LOG(debug, format __VA_OPT__(, ) __VA_ARGS__)
#define PALACE_LOG_TRACE(format, ...)                                          \
    PALACE_OBJECT_LOG(trace, format __VA_OPT__(, ) __VA_ARGS__)
#define PALACE_LOG_NO_OP(format, ...)

#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_FATAL
#define PALACE_LOG_FATAL_OPT PALACE_LOG_FATAL
#else
#define PALACE_LOG_FATAL_OPT PALACE_LOG_NO_OP
#endif
#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_ERROR
#define PALACE_LOG_ERROR_OPT PALACE_LOG_ERROR
#else
#define PALACE_LOG_ERROR_OPT PALACE_LOG_NO_OP
#endif
#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_WARNING
#define PALACE_LOG_WARNING_OPT PALACE_LOG_WARNING
#else
#define PALACE_LOG_WARNING_OPT PALACE_LOG_NO_OP
#endif
#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_INFO
#define PALACE_LOG_INFO_OPT PALACE_LOG_INFO
#else
#define PALACE_LOG_INFO_OPT PALACE_LOG_NO_OP
#endif
#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_DEBUG
#define PALACE_LOG_DEBUG_OPT PALACE_LOG_DEBUG
#else
#define PALACE_LOG_DEBUG_OPT PALACE_LOG_NO_OP
#endif
#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_TRACE
#define PALACE_LOG_TRACE_OPT PALACE_LOG_TRACE
#else
#define PALACE_LOG_TRACE_OPT PALACE_LOG_NO_OP
#endif

#define PALACE_OBJECT_DATA(object, parent_class, description)                  \
public:                                                                        \
    static constexpr const char *s_objectName = #object;                       \
    static constexpr const char *s_parentObjectName = #parent_class;           \
    static constexpr const char *s_description = description;

class EngineObject {
    PALACE_OBJECT_DATA(EngineObject, , "Base object type.");

    friend EngineContext;

public:
    EngineObject();
    virtual ~EngineObject();

    inline EngineContext *context() const { return m_context; }
    inline Logger &logger() const { return context()->logger(); }
    inline void addObject(EngineObject *object) {
        object->m_context = m_context;
        object->m_parent = this;
        object->m_id = m_context->newId();
    }

    ObjectId id() const { return m_id; }

private:
    EngineContext *m_context;
    EngineObject *m_parent;

    ObjectId m_id;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP */
