#include <gtest/gtest.h>

#include "../include/memory/heap_allocator.hpp"

bool checkAlignment(void *p, int alignment) {
    union PointerToUint64 {
        void *p;
        std::uint64_t l;
    };

    PointerToUint64 conversion;
    conversion.p = p;

    return (conversion.l % alignment) == 0;
}

TEST(HeapAllocatorTest, SanityTest) {
    int *data = debug_palace_aligned_new(int, 16);
    *data = 1;

    EXPECT_TRUE(checkAlignment(static_cast<void *>(data), 16));

    palace::HeapAllocator::get().free(data);

    EXPECT_EQ(data, nullptr);
}

TEST(HeapAllocatorTest, AlignmentTest) {
    for (int i = 0; i < 256; ++i) {
        int *data = debug_palace_aligned_new(int, 256);
        *data = 1;

        EXPECT_TRUE(checkAlignment(static_cast<void *>(data), 256));

        palace::HeapAllocator::get().free(data);
        EXPECT_EQ(data, nullptr);
    }

    EXPECT_EQ(palace::HeapAllocator::get().getActiveAllocations(), 0);
}
