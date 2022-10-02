#pragma once

#include <iostream>

#ifdef PALACE_DEBUG
#define PALACE_ASSERT(x, ...) palace::assert(x, __VA_ARGS__)
#else
#define PALACE_ASSERT(x, ...)
#endif

namespace palace {

template<typename... ARGS>
void assert(bool condition, const ARGS &...args)
{
    if (!condition) {
#if defined(REBAR_COMPILER_MSVC) || defined(REBAR_COMPILER_INTEL)
        __debugbreak();
#elif defined(REBAR_COMPILER_CLANG)
        __builtin_debugtrap();
#elif defined(REBAR_COMPILER_GCC)
        __builtin_trap();
#endif
    }
}

}// namespace palace
