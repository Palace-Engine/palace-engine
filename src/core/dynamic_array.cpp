#include "../../include/core/dynamic_array.hpp"

palace::HeapAllocator *palace::DynamicArrayAllocator::s_defaultAllocator =
        new palace::HeapAllocator;
