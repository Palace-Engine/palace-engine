#include "../../include/logging/log_target.hpp"

#include <ctime>
#include <sstream>

palace::LogTarget::LogTarget() {
    m_maximumLogLevel = LogLevel::Trace;
    m_timestampBuffer = new char[256];
}

palace::LogTarget::~LogTarget() { delete[] m_timestampBuffer; }

void palace::LogTarget::log(LogLevel level, std::string_view message,
                            bool critical) {
    if (static_cast<unsigned int>(level) >
        static_cast<unsigned int>(m_maximumLogLevel)) {
        return;
    }

    std::stringstream ss;
    ss << timestamp() << " | " << logLevelToString(level) << " | " << message
       << "\n";
    log(ss.str(), critical);
}

void palace::LogTarget::close() { onClose(); }

std::string_view palace::LogTarget::logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Debug:
            return "DEBUG  ";
        case LogLevel::Error:
            return "ERROR  ";
        case LogLevel::Fatal:
            return "FATAL  ";
        case LogLevel::Info:
            return "INFO   ";
        case LogLevel::Trace:
            return "TRACE  ";
        case LogLevel::Warning:
            return "WARNING";
        default:
            return "UNKNOWN";
    }
}

std::string_view palace::LogTarget::timestamp() {
    std::time_t result = std::time(nullptr);
    strftime(m_timestampBuffer, 64, "%Y-%m-%d %H:%M:%S",
                                   std::localtime(&result));

    return m_timestampBuffer;
}
