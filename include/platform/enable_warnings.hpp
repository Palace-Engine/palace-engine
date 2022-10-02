#if defined(REBAR_COMPILER_MSVC)
#pragma warning(pop)
#elif defined(REBAR_COMPILER_CLANG)
#pragma GCC diagnostic pop
#elif defined(REBAR_COMPILER_GCC)
#pragma GCC diagnostic pop
#elif defined(REBAR_COMPILER_INTEL)
#pragma warning(pop)
#endif
