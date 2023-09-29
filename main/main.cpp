#include <iostream>
#include <geometry.hpp>

using namespace geometry;

int main()
{
    double a = NAN;
    double b = 0;
    Point point {a/b, -2, 3};
    std::cout << point.valid() << "\n";

    Point point1{1, 0, 1};
    Point point2{0, 1, 1};
    Point point3{-1, 0, 1};
    Plane plane{point1, point2, point3};
    plane.print();
    std::cout << "\n";

    Point point4{2, 1, 5};
    Point point5{-6, -3, -15};
    Vector vec1(point4);
    Vector vec2(point5);
    std::cout << collinear(vec1, vec2) << "\n";

    Point point6{100, -228, 1};
    Point point7{1488, 21, 1};
    Point point8{777, 1337.0, 1};
    Plane plane2{point6, point7, point8};
    plane2.print();
    std::cout << "\n";

    Point point9{100, -1, 228};
    Point point10{1488, -1, 1010};
    Point point11{777, -1, 21};
    Plane plane3{point9, point10, point11};
    plane3.print();
    std::cout << "\n";

    Line intersec = plane_intersection(plane2, plane3);

    intersec.print();
    std::cout << "\n";

    //point.print();
    return 0;
}