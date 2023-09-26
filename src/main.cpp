#include <iostream>
#include "geometry.hpp"

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

    Point point4{2, 1, 5};
    Point point5{-6, -3, -15};
    Vector vec1(point4);
    Vector vec2(point5);
    std::cout << Vector::collinear(vec1, vec2) << "\n";
    //point.print();
    return 0;
}