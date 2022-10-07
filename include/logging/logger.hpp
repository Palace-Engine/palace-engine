#ifndef ATG_PALACE_ENGINE_LOGGER_HPP
#define ATG_PALACE_ENGINE_LOGGER_HPP

#include "../core/dynamic_array.hpp"
#include "../logging/log_level.hpp"
#include "../logging/log_target.hpp"
#include "../memory/heap_allocator.hpp"

#include <string_view>

namespace palace {

#define PALACE_LOGGER_LOG_PROTOTYPE(name, level)                               \
    template<typename... Args>                                                 \
    void name(std::string_view format, Args... args) {                         \
        log(level, format, args...);                                           \
    }

class Logger {
public:
    static void setDefaultHeapAllocator(HeapAllocator *allocator) {
        s_defaultAllocator = allocator;
    }

private:
    static HeapAllocator *s_defaultAllocator;

public:
    Logger();
    ~Logger();

    template<typename T_LogTarget>
    T_LogTarget *addTarget() {
        T_LogTarget *newTarget = m_allocator->palace_new(T_LogTarget);
        m_targets.append(static_cast<LogTarget *>(newTarget));

        return newTarget;
    }

    PALACE_LOGGER_LOG_PROTOTYPE(fatal, LogLevel::Fatal);
    PALACE_LOGGER_LOG_PROTOTYPE(error, LogLevel::Error);
    PALACE_LOGGER_LOG_PROTOTYPE(warn, LogLevel::Warning);
    PALACE_LOGGER_LOG_PROTOTYPE(info, LogLevel::Info);
    PALACE_LOGGER_LOG_PROTOTYPE(debug, LogLevel::Debug);
    PALACE_LOGGER_LOG_PROTOTYPE(trace, LogLevel::Trace);

private:
    template<typename... Args>
    void log(LogLevel level, std::string_view format, Args... args) {
        const size_t capacity = m_buffer.capacity();
        const size_t size =
                snprintf(m_buffer.data(), capacity + 1, format.data(), args...);
        if (size > m_buffer.capacity()) {
            m_buffer.resize(size);
            snprintf(m_buffer.data(), size + 1, format.data(), args...);
        }

        const size_t n = m_targets.size();
        for (size_t i = 0; i < n; ++i) {
            m_targets[i]->log(level, m_buffer);
        }
    }

private:
    DynamicArray<LogTarget *> m_targets;
    HeapAllocator *m_allocator;
    std::string m_buffer;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_LOGGER_HPP */
