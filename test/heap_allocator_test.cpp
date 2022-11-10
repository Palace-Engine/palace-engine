#include <gtest/gtest.h>

#include "../include/memory/heap_allocator.hpp"

bool checkAlignment(void *p, size_t alignment) {
    union PointerToUint64 {
        void *p;
        std::uint64_t l;
    };

    PointerToUint64 conversion;
    conversion.p = p;

    return (conversion.l % alignment) == 0;
}

TEST(HeapAllocatorTest, SanityTest) {
    palace::HeapAllocator allocator;
    int *data = allocator.debug_palace_aligned_new(int, 16);
    *data = 1;

    EXPECT_TRUE(checkAlignment(static_cast<void *>(data), 16));

    allocator.debug_palace_aligned_free(data);
    EXPECT_EQ(data, nullptr);
}

TEST(HeapAllocatorTest, AlignmentTest) {
    palace::HeapAllocator allocator;
    for (int i = 0; i < 256; ++i) {
        int *data = allocator.debug_palace_aligned_new(int, 256);
        *data = 1;

        EXPECT_TRUE(checkAlignment(static_cast<void *>(data), 256));

        allocator.debug_palace_aligned_free(data);
        EXPECT_EQ(data, nullptr);
    }

    EXPECT_EQ(allocator.getActiveAllocations(), 0);
}

struct DestructorChecker {
    ~DestructorChecker() { (*target)++; }
    int *target = nullptr;
};

TEST(HeapAllocatorTest, DestructionTest) {
    palace::HeapAllocator allocator;
    DestructorChecker *test =
            allocator.debug_palace_new_array(DestructorChecker, 128);

    int counter = 0;
    for (int i = 0; i < 128; ++i) { test[i].target = &counter; }

    allocator.debug_palace_free_array(test);

    EXPECT_EQ(counter, 128);
    EXPECT_EQ(allocator.getActiveAllocations(), 0);
}

TEST(HeapAllocatorTest, DestructionTestAlignedArray) {
    palace::HeapAllocator allocator;
    DestructorChecker *test = allocator.debug_palace_aligned_new_array(
            DestructorChecker, 16, 128);

    int counter = 0;
    for (int i = 0; i < 128; ++i) { test[i].target = &counter; }

    allocator.debug_palace_aligned_free_array(test);

    EXPECT_EQ(counter, 128);
    EXPECT_EQ(allocator.getActiveAllocations(), 0);
}

TEST(HeapAllocatorTest, MemoryLeakTest) {
    palace::HeapAllocator allocator;
    int **test = allocator.debug_palace_new_array(int *, 128);

    const int line = __LINE__ + 1;
    for (int i = 0; i < 128; ++i) { test[i] = allocator.debug_palace_new(int); }
    for (int i = 0; i < 127; ++i) { allocator.debug_palace_free(test[i]); }

    allocator.debug_palace_free_array(test);

    EXPECT_EQ(allocator.getActiveAllocations(), 1);
    EXPECT_EQ(allocator.getActiveAllocation(0).filename,
              __FILE__);
    EXPECT_EQ(allocator.getActiveAllocation(0).line, line);

    allocator.clearRecords();
}
