#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

static const double EPSILON = 10e-8;

class Point
{
public:
    double x = NAN, y = NAN, z = NAN;

    Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    Point() {}

    void print() const
    {
        std::cout << "(" << x << ";" << y << ")" << "\n"; 
    }

    bool is_valid() const
    {
        return (x == x && y == y);
    }

    bool equal(const Point &rhs) const
    {
        assert(is_valid() && rhs.is_valid());
        return (std::abs(x - rhs.x) < EPSILON) && (std::abs(y - rhs.y) < EPSILON);
    }
};

