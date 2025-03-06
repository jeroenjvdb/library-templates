#include <CppUTest/TestHarness.h>

extern "C"
{
#include "{{cookiecutter.project_name}}/{{cookiecutter.module_name}}.h"
}

// clang-format off
TEST_GROUP(test_{{cookiecutter.module_name}})
{
    void setup()
    {
    }

    void teardown()
    {
    }
};
// clang-format on

TEST(test_{{cookiecutter.module_name}}, first_test)
{
    FAIL("This test should fail");
}