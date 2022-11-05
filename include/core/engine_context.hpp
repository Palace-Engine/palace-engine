#ifndef ATG_PALACE_ENGINE_ENGINE_CONTEXT_HPP
#define ATG_PALACE_ENGINE_ENGINE_CONTEXT_HPP

#include "../logging/logger.hpp"

namespace palace {

class EngineContext {
public:
    EngineContext();
    ~EngineContext();

    inline Logger &logger() { return m_logger; }

private:
    Logger m_logger;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_ENGINE_CONTEXT_HPP */
