#include "../../include/core/object_container.hpp"

palace::HeapAllocator *palace::ObjectContainerAllocator::s_defaultAllocator =
        new palace::HeapAllocator;
