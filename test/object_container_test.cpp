#include <gtest/gtest.h>

#include "../include/core/object_container.hpp"

class TestBase : public palace::EngineObject {};
class TestChild : public TestBase {};

TEST(ObjectContainerTest, SanityTest) {
    palace::ObjectContainer<TestBase, TestChild> test;
}
