#include "../../include/memory/default_allocator.hpp"

#include "../../include/core/dynamic_array.hpp"

palace::HeapAllocator *palace::default_allocator = nullptr;

void palace::initializeAllocators() {
    default_allocator = new palace::HeapAllocator;
    DynamicArrayAllocator::s_defaultAllocator = default_allocator;
}
