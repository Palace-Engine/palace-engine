#include <gtest/gtest.h>

#include "../include/core/object_container.hpp"

class TestBase {};
class TestChild : public TestBase {};

TEST(ObjectContainerTest, SanityTest) {
    palace::ObjectContainer<TestBase, TestChild> test;
    palace::ObjectContainer<TestBase, TestBase> *ptest = test.toBase();
}
