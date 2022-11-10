#include <gtest/gtest.h>

#include "../include/core/dynamic_array.hpp"
#include "../include/memory/default_allocator.hpp"

TEST(DynamicArrayTest, SanityTest) {
    palace::DynamicArray<int> d_arr;
    d_arr.resize(128);

    for (int i = 0; i < 128; ++i) { d_arr.emplace(i); }

    EXPECT_EQ(d_arr.size(), 128);
    EXPECT_EQ(d_arr.capacity(), 128);

    for (size_t i = 0; i < 128; ++i) { EXPECT_EQ(d_arr[i], i); }

    d_arr.free();

    EXPECT_EQ(d_arr.allocator()->getActiveAllocations(), 0);
}

TEST(DynamicArrayTest, Grow) {
    palace::DynamicArray<int> d_arr;
    d_arr.resize(1);

    for (int i = 0; i < 128; ++i) { d_arr.append(i); }

    EXPECT_EQ(d_arr.size(), 128);
    EXPECT_GT(d_arr.capacity(), 128);

    for (size_t i = 0; i < 128; ++i) { EXPECT_EQ(d_arr[i], static_cast<int>(i)); }

    d_arr.free();

    EXPECT_EQ(d_arr.allocator()->getActiveAllocations(), 0);
}

TEST(DynamicArrayTest, Insert) {
    palace::DynamicArray<int> d_arr;
    d_arr.resize(1);

    for (int i = 0; i < 128; ++i) { d_arr.insert(i, 0); }

    EXPECT_EQ(d_arr.size(), 128);
    EXPECT_GT(d_arr.capacity(), 128);

    for (size_t i = 0; i < 128; ++i) { EXPECT_EQ(d_arr[i], 128 - static_cast<int>(i) - 1); }

    d_arr.free();

    EXPECT_EQ(d_arr.allocator()->getActiveAllocations(), 0);
}

TEST(DynamicArrayTest, FastRemove) {
    palace::DynamicArray<int> d_arr;
    d_arr.resize(128);

    for (int i = 0; i < 128; ++i) { d_arr.emplace(i); }
    for (int i = 0; i < 128; ++i) { d_arr.fastRemove(0); }

    EXPECT_EQ(d_arr.size(), 0);

    d_arr.free();

    EXPECT_EQ(d_arr.allocator()->getActiveAllocations(), 0);
}

TEST(DynamicArrayTest, Remove) {
    palace::DynamicArray<int> d_arr;
    d_arr.resize(128);

    for (int i = 0; i < 128; ++i) { d_arr.emplace(i); }
    for (int i = 0; i < 128; ++i) {
        EXPECT_EQ(d_arr[0], i);
        d_arr.remove(0);

        if (d_arr.size() > 0) { EXPECT_EQ(d_arr[0], i + 1); }
    }

    EXPECT_EQ(d_arr.size(), 0);

    d_arr.free();

    EXPECT_EQ(d_arr.allocator()->getActiveAllocations(), 0);
}
