#pragma once

#include <iostream>
#include <string_view>

#ifdef PALACE_DEBUG
#define palace_assert(condition, ...)                                          \
    palace::internalAssert((condition),                                        \
                           __FILE__, __LINE__ __VA_OPT__(, ) __VA_ARGS__)
#else
#define palace_assert(condition, ...)
#endif

namespace palace {

template<typename... ARGS>
void internalAssert(bool condition, std::string_view file, int line,
                    const ARGS &...args) {
    if (!condition) {
#if defined(PALACE_COMPILER_MSVC) || defined(PALACE_COMPILER_INTEL)
        __debugbreak();
#elif defined(PALACE_COMPILER_CLANG)
        __builtin_debugtrap();
#elif defined(PALACE_COMPILER_GCC)
        __builtin_trap();
#endif
    }
}

}// namespace palace
