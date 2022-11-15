#ifndef ATG_PALACE_ENGINE_RESULT_HPP
#define ATG_PALACE_ENGINE_RESULT_HPP

#include "../formatting/formatters.hpp"

namespace palace {

enum class Result {
    // Success
    Success,

    // Failure
    ErrorApiFailure,
    ErrorUnsupported,
    ErrorOutOfBounds
};

inline bool isSuccessful(Result result) { return result == Result::Success; }

}// namespace palace

PALACE_ENUM_FORMATTER_BEGIN(palace, Result)
PALACE_ENUM_FORMATTER_ENTRY(Success)
PALACE_ENUM_FORMATTER_ENTRY(ApiError)
PALACE_ENUM_FORMATTER_ENTRY(Unsupported)
PALACE_ENUM_FORMATTER_ENTRY(OutOfBounds)
PALACE_ENUM_FORMATTER_END()

#endif /* ATG_PALACE_ENGINE_RESULT_HPP */
