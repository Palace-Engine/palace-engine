#ifndef ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP
#define ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP

#include "engine_context.hpp"

namespace palace {

#define PALACE_ENGINE_LOG_LEVEL PALACE_ENGINE_LOG_LEVEL_DEBUG
#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_FATAL
#define PALACE_LOG_FATAL(format, ...)                                          \
    logger().fatal(format __VA_OPT__(, ) __VA_ARGS__
#else
#define PALACE_LOG_FATAL(format, ...)
#endif
#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_ERROR
#define PALACE_LOG_ERROR(format, ...)                                          \
    logger().error(format __VA_OPT__(, ) __VA_ARGS__
#else
#define PALACE_LOG_ERROR(format, ...)
#endif
#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_WARNING
#define PALACE_LOG_WARNING(format, ...)                                        \
    logger().warn(format __VA_OPT__(, ) __VA_ARGS__
#else
#define PALACE_LOG_WARNING(format, ...)
#endif
#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_INFO
#define PALACE_LOG_INFO(format, ...)                                           \
    logger().info(format __VA_OPT__(, ) __VA_ARGS__)
#else
#define PALACE_LOG_INFO(format, ...)
#endif
#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_DEBUG
#define PALACE_LOG_DEBUG(format, ...)                                          \
    logger().debug(format __VA_OPT__(, ) __VA_ARGS__)
#else
#define PALACE_LOG_DEBUG(level, format, ...)
#endif
#if defined(PALACE_ENGINE_LOG_LEVEL) and                                       \
        PALACE_ENGINE_LOG_LEVEL >= PALACE_ENGINE_LOG_LEVEL_TRACE
#define PALACE_LOG_TRACE(format, ...)                                          \
    logger().trace(format __VA_OPT__(, ) __VA_ARGS__)
#else
#define PALACE_LOG_TRACE(format, ...)
#endif

class EngineObject {
public:
    EngineObject();
    virtual ~EngineObject();

    inline void setContext(EngineContext *context) { m_context = context; }
    inline EngineContext *context() const { return m_context; }
    inline Logger &logger() const { return context()->logger(); }
    inline void addObject(EngineObject *object) {
        object->m_context = m_context;
        object->m_parent = this;
    }

private:
    EngineContext *m_context;
    EngineObject *m_parent;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP */
