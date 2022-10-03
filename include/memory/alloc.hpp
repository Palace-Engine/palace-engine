#ifndef ATG_PALACE_ENGINE_MEMORY_H
#define ATG_PALACE_ENGINE_MEMORY_H

#if defined(PALACE_COMPILER_MSVC)
#include <malloc.h>
#define palace_alloc(alignment, size) _aligned_malloc((size), (alignment))
#define palace_free(buffer) _aligned_free((buffer))
#elif defined(PALACE_COMPILER_GCC) || defined(PALACE_COMPILER_CLANG)
#include <stdlib.h>
#define palace_alloc(alignment, size) std::aligned_alloc((alignment), (size))
#define palace_free(buffer) std::free((buffer))
#elif defined(PALACE_COMPILER_INTEL)
#include <malloc.h>
#define palace_alloc(alignment, size) _mm_malloc((size), (alignment))
#define palace_free(buffer) _mm_free(buffer)
#else
static_assert("PALACE_COMPILER_* macro not defined")
#endif

#endif// ATG_PALACE_ENGINE_MEMORY_H
