#include <gtest/gtest.h>

#include "../include/logging/logger.hpp"

class TestLogTarget : public palace::LogTarget {
public:
    TestLogTarget() {}
    ~TestLogTarget() {}

    size_t logMessageCount() const { return m_logMessages.size(); }
    std::string getLogMessage(size_t i) const { return m_logMessages[i]; }

private:
    virtual void log(std::string_view message, bool critical) override {
        m_logMessages.append(message.data());
    }

    palace::DynamicArray<std::string> m_logMessages;
};

TEST(LoggerTest, SanityTest) {
    palace::Logger logger;

    TestLogTarget *logTarget = logger.addTarget<TestLogTarget>();

    logger.info("TEST");
    EXPECT_EQ(logTarget->logMessageCount(), 1);

    std::string msg = logTarget->getLogMessage(0);
    EXPECT_EQ(msg.substr(32, 4), "TEST");
}
