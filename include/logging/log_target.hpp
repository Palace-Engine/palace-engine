#ifndef ATG_PALACE_ENGINE_LOG_TARGET_HPP
#define ATG_PALACE_ENGINE_LOG_TARGET_HPP

#include "log_level.hpp"

#include <string_view>
#include <string>

namespace palace {

class LogTarget {
public:
    LogTarget();
    virtual ~LogTarget();

    void log(LogLevel level, std::string_view message);

private:
    virtual void log(std::string_view message) = 0;

    static std::string_view logLevelToString(LogLevel level);
    std::string_view timestamp();

    char *m_timestampBuffer;
};

}// namespace palace

#endif// ATG_PALACE_ENGINE_LOG_TARGET_HPP
