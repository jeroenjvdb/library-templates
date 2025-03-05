#include <CppUTest/TestHarness.h>

extern "C" {
    #include "test/test.h"
}

TEST_GROUP(TestGroup)
{
    void setup() override
    {
    }

    void teardown() override
    {
    }
};

TEST(TestGroup, test_return_true)
{
    CHECK_TRUE(return_true());
}

TEST(TestGroup, test_return_false)
{
    CHECK_FALSE(return_false());
}
