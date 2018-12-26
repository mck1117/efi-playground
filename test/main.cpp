#include <iostream>

#include <can/can.h>

#include <gtest/gtest.h>

TEST(ExampleTest, TestFoo)
{
	EXPECT_EQ(foo(), 28);
}
