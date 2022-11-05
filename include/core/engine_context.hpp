#ifndef ATG_PALACE_ENGINE_ENGINE_CONTEXT_HPP
#define ATG_PALACE_ENGINE_ENGINE_CONTEXT_HPP

#include "../logging/logger.hpp"

namespace palace {

using ObjectId = unsigned long long;
static constexpr ObjectId InvalidId = -1;

class ApplicationContext;
class EngineContext {
public:
    EngineContext(ApplicationContext *applicationContext);
    virtual ~EngineContext();

    inline Logger &logger() { return m_logger; }
    ApplicationContext *applicationContext() { return m_applicationContext; }

    ObjectId newId() { return m_currentId++; }

protected:
    void registerApplicationContext();

private:
    ApplicationContext *m_applicationContext;
    Logger m_logger;
    ObjectId m_currentId;
};

}// namespace palace

#endif /* ATG_PALACE_ENGINE_ENGINE_CONTEXT_HPP */
