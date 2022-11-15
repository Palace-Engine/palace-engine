#ifndef ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP
#define ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP

#include "../formatting/formatting.hpp"
#include "engine_context.hpp"
#include "result.hpp"

#include <sstream>

namespace palace {

// Temporary.
#define PALACE_ENGINE_LOG_LEVEL PALACE_ENGINE_LOG_LEVEL_DEBUG

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
    PALACE_OBJECT_LOG(warn, format __VA_OPT__(, ) __VA_ARGS__)
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

// Final semicolon missing to avoid compiler warnings when it's added after the
// macro. It's desirable to manually type the semicolon because it avoids issues
// with MSVC's intellisense parser which seems to encounter issues when it's
// missing.
#define PALACE_OBJECT_DATA(object, parent_class, description)                  \
public:                                                                        \
    static constexpr const char *s_objectName = #object;                       \
    virtual const char *objectName() { return s_objectName; }                  \
    static constexpr const char *s_parentObjectName = #parent_class;           \
    static constexpr const char *s_description = description

class EngineObject {
    PALACE_OBJECT_DATA(EngineObject, , "Base object type.");

    friend EngineContext;

    template<typename, typename, size_t>
    friend class ObjectContainer;

public:
    EngineObject();
    virtual ~EngineObject();

    void free();

    inline EngineContext *context() const { return m_context; }
    inline Logger &logger() const { return context()->logger(); }
    inline void registerObject(EngineObject *object) {
        object->m_context = m_context;
        object->m_parent = this;
        object->m_id = m_context->newId();
    }

    inline ObjectId id() const { return m_id; }
    inline size_t index() const { return m_index; }

    inline void addReference() { ++m_references; }
    inline void removeReference() { --m_references; }
    inline size_t references() const { return m_references; }

    inline bool isDeleted() const { return m_deleted; }
    void setDeleted();
    inline void forceDelete() {
        m_deleted = true;
        m_references = 0;
    }

protected:
    virtual void free_();

private:
    EngineContext *m_context;
    EngineObject *m_parent;

    ObjectId m_id;
    size_t m_index;
    size_t m_references;
    bool m_deleted;
};

}// namespace palace

#define PALACE_OBJECT_FORMATTER(class_name, formatter_name)                    \
    namespace palace {                                                         \
    class formatter_name {                                                     \
    public:                                                                    \
        formatter_name(class_name *object) { m_object = object; }              \
                                                                               \
        inline class_name *object() const { return m_object; }                 \
                                                                               \
    private:                                                                   \
        class_name *m_object;                                                  \
    };                                                                         \
    }                                                                          \
    template<class CharT>                                                      \
    struct palace::format::formatter<palace::formatter_name, CharT> {          \
        constexpr auto parse(format_parse_context &ctx)                        \
                -> decltype(ctx.begin()) {                                     \
            if (ctx.begin() != ctx.end()) {                                    \
                throw format_error("Invalid format");                          \
            }                                                                  \
            return ctx.begin();                                                \
        }                                                                      \
        template<typename FormatContext>                                       \
        auto format(const palace::formatter_name &v, FormatContext &ctx)

#define PALACE_END_OBJECT_FORMATTER }

PALACE_OBJECT_FORMATTER(EngineObject, DefaultObjectFormatter) {
    return format_to(ctx.out(), "[{}, id=@{}]", v.object()->objectName(),
                     v.object()->id());
}
PALACE_END_OBJECT_FORMATTER;

#endif /* ATG_PALACE_ENGINE_ENGINE_OBJECT_HPP */
