#ifndef ATG_PALACE_ENGINE_LOG_TARGET_HPP
#define ATG_PALACE_ENGINE_LOG_TARGET_HPP

#include "log_level.hpp"

#include <string>
#include <string_view>

namespace palace {

class LogTarget {
public:
    LogTarget();
    virtual ~LogTarget();

    void setMaximumLogLevel(LogLevel level) { m_maximumLogLevel = level; }
    LogLevel maximumLogLevel() const { return m_maximumLogLevel; }

    void log(LogLevel level, std::string_view message, bool critical);
    void close();

private:
    virtual void log(std::string_view message, bool critical) = 0;
    virtual void onClose() {}

    static std::string_view logLevelToString(LogLevel level);
    std::string_view timestamp();

    char *m_timestampBuffer;
    LogLevel m_maximumLogLevel;
};

}// namespace palace

#endif// ATG_PALACE_ENGINE_LOG_TARGET_HPP
