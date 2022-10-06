#ifndef ATG_PALACE_ENGINE_DEFAULT_ALLOCATOR_H
#define ATG_PALACE_ENGINE_DEFAULT_ALLOCATOR_H

#include "heap_allocator.hpp"

namespace palace {
extern HeapAllocator *default_allocator;

void initializeAllocators();
}

#endif// ATG_PALACE_ENGINE_DEFAULT_ALLOCATOR_H
