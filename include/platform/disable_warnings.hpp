#if defined(REBAR_COMPILER_MSVC)
#pragma warning(push, 0)
#elif defined(REBAR_COMPILER_CLANG)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#elif defined(REBAR_COMPILER_GCC)
#pragma GCC diagnostic push
#elif defined(REBAR_COMPILER_INTEL)
#pragma warning(push, 0)
#endif
