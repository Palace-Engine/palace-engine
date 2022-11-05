#include "../../include/logging/logger.hpp"

#include "../../include/logging/log_target.hpp"

palace::HeapAllocator *palace::Logger::s_defaultAllocator =
        new palace::HeapAllocator;

palace::Logger::Logger() { m_allocator = s_defaultAllocator; }

palace::Logger::~Logger() {}

void palace::Logger::close() {
    const size_t n = m_targets.size();
    for (size_t i = 0; i < n; ++i) { m_targets[i]->close(); }
}
