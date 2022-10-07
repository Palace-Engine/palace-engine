#include "../../include/logging/log_target.hpp"

#include <ctime>
#include <sstream>

palace::LogTarget::LogTarget() { m_timestampBuffer = new char[256]; }

palace::LogTarget::~LogTarget() {}

void palace::LogTarget::log(LogLevel level, std::string_view message) {
    std::stringstream ss;
    ss << std::string(timestamp()) << " | " << std::string(logLevelToString(level))
       << " | " << std::string(message) << "\n";
    log(ss.str());
}

std::string_view palace::LogTarget::logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Debug:
            return "DEBUG";
        case LogLevel::Error:
            return "ERROR";
        case LogLevel::Fatal:
            return "FATAL";
        case LogLevel::Info:
            return "INFO";
        case LogLevel::Trace:
            return "TRACE";
        case LogLevel::Warning:
            return "WARNING";
        default:
            return "UNKNOWN";
    }
}

std::string_view palace::LogTarget::timestamp() {
    std::time_t result = std::time(nullptr);
    const size_t length =
            strftime(m_timestampBuffer, 64, "%Y-%m-%d %H:%M:%S",
                     std::localtime(&result));

    return m_timestampBuffer;
}
