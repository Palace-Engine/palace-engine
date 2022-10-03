#pragma once

#include <iostream>

#ifdef PALACE_DEBUG
#define palace_assert(x, ...) palace::internalAssert(x __VA_OPT__(,) __VA_ARGS__)
#else
#define palace_assert(x, ...)
#endif

namespace palace {

template<typename... ARGS>
void internalAssert(bool condition, const ARGS &...args) {
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
