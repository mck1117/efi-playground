#include <gtest/gtest.h>

#include <core/config/ConfigField.h>

const char* str = "hello_world";

TEST(configtest, foo)
{
    test_config_big t;

    PrefixStack prefix;
    prefix.push("root_");

    std::stringstream str;

    t.Print(str, &t, prefix, "test_");

    std::cout << str.str();

    std::cout << "size of test_config: " << sizeof(t);
}
