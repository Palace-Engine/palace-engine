#if defined(PALACE_COMPILER_MSVC)
#pragma warning(push, 0)
#pragma warning(disable: 5105)
#elif defined(PALACE_COMPILER_CLANG)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#elif defined(PALACE_COMPILER_GCC)
#pragma GCC diagnostic push
#elif defined(PALACE_COMPILER_INTEL)
#pragma warning(push, 0)
#endif
