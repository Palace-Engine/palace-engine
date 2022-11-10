#include "../../../include/logging/targets/file_log_target.hpp"

#include <sstream>
#include <string>

palace::FileLogTarget::FileLogTarget() { m_timestampBuffer = new char[256]; }

palace::FileLogTarget::~FileLogTarget() { delete[] m_timestampBuffer; }

bool palace::FileLogTarget::newFile(std::string_view fname,
                                    std::string_view path,
                                    std::string_view extension,
                                    bool timestamp) {
    if (m_file.is_open()) close();

    std::stringstream ss;
    if (timestamp) {
        ss << path << "/" << this->timestamp() << "_" << fname << extension;
    } else {
        ss << path << "/" << fname << extension;
    }

    m_file.open(ss.str(), std::ios::out);

    return m_file.is_open();
}

bool palace::FileLogTarget::resume(std::string_view filename) {
    if (m_file.is_open()) close();

    m_file.open(std::string(filename), std::ios::out | std::ios::app);

    return m_file.is_open();
}

void palace::FileLogTarget::log(std::string_view message, bool critical) {
    m_file << message;

    if (critical) { m_file.flush(); }
}

void palace::FileLogTarget::onClose() { m_file.close(); }

std::string_view palace::FileLogTarget::timestamp() const {
    std::time_t result = std::time(nullptr);
    strftime(m_timestampBuffer, 64, "%Y%m%d_T%H%M%S",
                                   std::localtime(&result));

    return m_timestampBuffer;
}
