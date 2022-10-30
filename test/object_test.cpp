#include <gtest/gtest.h>

#include "../include/core/object.hpp"

class BaseObject : public palace::Object {
public:
    BaseObject() {}
};

class ParticularObject0 : public BaseObject {
public:
    ParticularObject0() {}
    virtual ~ParticularObject0() {}

    void initialize(int v0, int v1) {
        m_v0 = v0;
        m_v1 = v1;
    }

    inline int v0() const { return m_v0; }
    inline int v1() const { return m_v1; }

private:
    int m_v0 = -1, m_v1 = -1;
};

class ParticularObject1 : public BaseObject {
public:
    ParticularObject1() {}
    virtual ~ParticularObject1() {}

    void initialize(int v0, int v1, int v2) {
        m_v0 = v0;
        m_v1 = v1;
        m_v2 = v2;
    }

    inline int v0() const { return m_v0; }
    inline int v1() const { return m_v1; }
    inline int v2() const { return m_v2; }

private:
    int m_v0 = -1, m_v1 = -1, m_v2 = -1;
};

class Root : public palace::Object {
public:
    Root() : palace::Object(), Objects0(this), Objects1(this) {}

    ObjectList<ParticularObject0> Objects0;
    ObjectList<ParticularObject1> Objects1;
};

TEST(ObjectTest, SanityTest) {
    Root root;
    ParticularObject0 *obj0 = root.Objects0.create();
    ParticularObject1 *obj1 = root.Objects1.create();
    EXPECT_EQ(root.activeObjects(), 2);

    EXPECT_EQ(root.Objects0.size(), 1);
    EXPECT_EQ(root.Objects1.size(), 1);

    root.Objects0.free(obj0);
    root.Objects1.free(obj1);

    EXPECT_EQ(obj0, nullptr);
    EXPECT_EQ(obj1, nullptr);

    EXPECT_EQ(root.Objects0.size(), 0);
    EXPECT_EQ(root.Objects1.size(), 0);

    EXPECT_EQ(root.activeObjects(), 0);
}
