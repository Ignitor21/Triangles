#include <iostream>
#include <gtest/gtest.h>
#include "geometry.hpp"

using namespace geometry;

TEST(POINT, point_methods)
{
    Point p1(5.0, 228, -1337.1488);
    double a = NAN;
    Point p2{a, 10, 15};
    Point p3(0, 0, 0);
    
    EXPECT_TRUE(p1.valid());
    EXPECT_FALSE(p2.valid());
    EXPECT_FALSE(p2 == p3);
    EXPECT_FALSE(p2 == p2);
    EXPECT_TRUE(p1 == p1);
}

TEST(PLANES_INTERSECTION, line)
{
    Point point1{100, -228, 1};
    Point point2{1488, 21, 1};
    Point point3{777, 1337.0, 1};
    Plane plane1{point1, point2, point3};

    Point point4{100, -1, 228};
    Point point5{1488, -1, 1010};
    Point point6{777, -1, 21};
    Plane plane2{point4, point5, point6};

    Line intersec = plane_intersection(plane1, plane2);
    Line ans{{21, 0, 0}, {5, -1, 1}};
    EXPECT_TRUE(ans.point_belongs(intersec.point) && collinear(ans.direction, intersec.direction));
}

TEST(PLANES_INTERSECTION, coincident)
{
    Point point1{5000000.000001, -228, 749};
    Point point2{5000000.000001, 21, 2121.2121};
    Point point3{5000000.000001, 1337.0, 98765.4321};
    Plane plane1{point1, point2, point3};

    Point point4{5000000.000001, -0.32131245, 228};
    Point point5{5000000.000001, 777.777, 1010};
    Point point6{5000000.000001, -1, 21};
    Plane plane2{point4, point5, point6};

    Line intersec = plane_intersection(plane1, plane2);
    EXPECT_TRUE(intersec.direction.null() && !intersec.point.valid());
}

TEST(PLANES_INTERSECTION, parallel)
{
    Point point1{5000000.000001, -228, 749};
    Point point2{5000000.000001, 21, 2121.2121};
    Point point3{5000000.000001, 1337.0, 98765.4321};
    Plane plane1{point1, point2, point3};

    Point point4{5000000.000008, -0.32131245, 228};
    Point point5{5000000.000008, 777.777, 1010};
    Point point6{5000000.000008, -1, 21};
    Plane plane2{point4, point5, point6};

    Line intersec = plane_intersection(plane1, plane2);
    EXPECT_TRUE(!intersec.direction.valid() && !intersec.point.valid());
}

int main(int argc, char** argv)
{   
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}