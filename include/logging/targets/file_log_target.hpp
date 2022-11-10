#ifndef ATG_PALACE_ENGINE_FILE_LOG_TARGET_HPP
#define ATG_PALACE_ENGINE_FILE_LOG_TARGET_HPP

#include "../log_target.hpp"

#include <fstream>

namespace palace {

class FileLogTarget : public LogTarget {
public:
    FileLogTarget();
    virtual ~FileLogTarget();

    bool newFile(std::string_view filename, std::string_view path = ".",
                 std::string_view extension = ".log", bool timestamp = true);
    bool resume(std::string_view filename);

private:
    virtual void log(std::string_view message, bool critical) override;
    virtual void onClose() override;

    std::string_view timestamp() const;
    std::fstream m_file;
    char *m_timestampBuffer;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_FILE_LOG_TARGET_HPP */
