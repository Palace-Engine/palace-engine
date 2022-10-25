#if defined(PALACE_COMPILER_MSVC)
#pragma warning(pop)
#elif defined(PALACE_COMPILER_CLANG)
#pragma GCC diagnostic pop
#elif defined(PALACE_COMPILER_GCC)
#pragma GCC diagnostic pop
#elif defined(PALACE_COMPILER_INTEL)
#pragma warning(pop)
#endif
