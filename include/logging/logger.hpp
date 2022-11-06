#ifndef ATG_PALACE_ENGINE_LOGGER_HPP
#define ATG_PALACE_ENGINE_LOGGER_HPP

#include "../core/dynamic_array.hpp"
#include "../logging/log_level.hpp"
#include "../logging/log_target.hpp"
#include "../memory/heap_allocator.hpp"
#include "../formatting/formatters.hpp"

#include <string_view>

namespace palace {

#define PALACE_LOGGER_LOG_PROTOTYPE(name, level)                               \
    void name(std::string_view formatted) { log(level, formatted); }

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

    void close();

    PALACE_LOGGER_LOG_PROTOTYPE(fatal, LogLevel::Fatal);
    PALACE_LOGGER_LOG_PROTOTYPE(error, LogLevel::Error);
    PALACE_LOGGER_LOG_PROTOTYPE(warn, LogLevel::Warning);
    PALACE_LOGGER_LOG_PROTOTYPE(info, LogLevel::Info);
    PALACE_LOGGER_LOG_PROTOTYPE(debug, LogLevel::Debug);
    PALACE_LOGGER_LOG_PROTOTYPE(trace, LogLevel::Trace);

private:
    void log(LogLevel level, std::string_view formatted) {
        if (static_cast<unsigned int>(level) >
                    static_cast<unsigned int>(m_maximumLogLevel) ||
            m_targets.size() == 0) {
            return;
        }

        const bool critical = static_cast<unsigned int>(level) <=
                              static_cast<unsigned int>(LogLevel::Error);
        const size_t n = m_targets.size();
        for (size_t i = 0; i < n; ++i) {
            m_targets[i]->log(level, formatted, critical);
        }
    }

private:
    DynamicArray<LogTarget *> m_targets;
    HeapAllocator *m_allocator;
    std::string m_buffer;
    LogLevel m_maximumLogLevel;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_LOGGER_HPP */
