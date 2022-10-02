#ifndef ATG_PALACE_ENGINE_PLATFORM_HPP
#define ATG_PALACE_ENGINE_PLATFORM_HPP

#include "../types/string.hpp"

namespace palace {

enum class Platform { Linux, Windows, Unknown };

void getName(Platform platform, string *target);

}// namespace palace

#endif /* ATG_PALACE_ENGINE_PLATFORM_HPP */
