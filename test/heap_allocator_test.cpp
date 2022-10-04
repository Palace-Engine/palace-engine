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

    debug_palace_aligned_free(data);
    EXPECT_EQ(data, nullptr);
}

TEST(HeapAllocatorTest, AlignmentTest) {
    for (int i = 0; i < 256; ++i) {
        int *data = debug_palace_aligned_new(int, 256);
        *data = 1;

        EXPECT_TRUE(checkAlignment(static_cast<void *>(data), 256));

        debug_palace_aligned_free(data);
        EXPECT_EQ(data, nullptr);
    }

    EXPECT_EQ(palace::HeapAllocator::get().getActiveAllocations(), 0);
}

struct DestructorChecker {
    ~DestructorChecker() { (*target)++; }
    int *target = nullptr;
};

TEST(HeapAllocatorTest, DestructionTest) {
    DestructorChecker *test = debug_palace_new_array(DestructorChecker, 128);

    int counter = 0;
    for (int i = 0; i < 128; ++i) { test[i].target = &counter; }

    debug_palace_free_array(test);

    EXPECT_EQ(counter, 128);
    EXPECT_EQ(palace::HeapAllocator::get().getActiveAllocations(), 0);
}

TEST(HeapAllocatorTest, DestructionTestAlignedArray) {
    DestructorChecker *test =
            debug_palace_aligned_new_array(DestructorChecker, 16, 128);

    int counter = 0;
    for (int i = 0; i < 128; ++i) { test[i].target = &counter; }

    debug_palace_aligned_free_array(test);

    EXPECT_EQ(counter, 128);
    EXPECT_EQ(palace::HeapAllocator::get().getActiveAllocations(), 0);
}

TEST(HeapAllocatorTest, MemoryLeakTest) {
    int **test = debug_palace_new_array(int *, 128);

    const int line = __LINE__ + 1;
    for (int i = 0; i < 128; ++i) { test[i] = debug_palace_new(int); }
    for (int i = 0; i < 127; ++i) { debug_palace_free(test[i]); }

    debug_palace_free_array(test);

    EXPECT_EQ(palace::HeapAllocator::get().getActiveAllocations(), 1);
    EXPECT_EQ(palace::HeapAllocator::get().getActiveAllocation(0).filename,
              __FILE__);
    EXPECT_EQ(palace::HeapAllocator::get().getActiveAllocation(0).line, line);
}
