#include <iostream>
#include <gtest/gtest.h>
#include "geometry.hpp"

using namespace geometry;

TEST(POINT, Subtest)
{
    Point p1(5.0, 228, -1337.1488);
    double a = NAN;
    Point p2{a, 10, 15};
    Point p3(0, 0, 0);
    EXPECT_TRUE(p1.valid());
    EXPECT_FALSE(p2.valid());
    EXPECT_FALSE(p2 == p3);
    EXPECT_TRUE(p2 == p2);
}

int main(int argc, char** argv)
{   
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}