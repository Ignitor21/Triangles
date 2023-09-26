#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

static const double EPSILON = 10e-8;

bool is_equal(double lhs, double rhs)
{
    return (std::abs(lhs - rhs) < EPSILON);
}

class Point
{
public:

    double x = NAN, y = NAN, z = NAN;

    Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    Point() {}

    void print() const
    {
        std::cout << "(" << x << ";" << y << ";" << z << ")" << "\n"; 
    }

    bool valid() const
    {
        return (std::isfinite(x) && std::isfinite(y) && std::isfinite(z));
    }

    bool equal(const Point &rhs) const
    {
        assert(valid() && rhs.valid());
        return ((std::abs(x - rhs.x) < EPSILON) && (std::abs(y - rhs.y) < EPSILON) && (std::abs(z - rhs.z) < EPSILON));
    }
};

class Vector
{
public:
    double x = NAN, y = NAN, z = NAN;

    Vector(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    Vector(const Point& point) : x(point.x), y(point.y), z(point.z) {}
    Vector() {}

    void print() const
    {
        std::cout << "(" << x << ";" << y << ";" << z << ")" << "\n"; 
    }

    bool valid() const
    {
        return (std::isfinite(x) && std::isfinite(y) && std::isfinite(z));
    }

    double scalar_mult(const Vector& vec1, const Vector& vec2) const
    {
        assert(vec1.valid() && vec2.valid());
        return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z); 
    }

    static Vector vector_mult(const Vector& vec1, const Vector& vec2)
    {
        assert(vec1.valid() && vec2.valid());
        Vector ans;
        ans.x = vec1.y*vec2.z - vec1.z*vec2.y;
        ans.y = vec1.z*vec2.x - vec1.x*vec2.z;
        ans.z = vec1.z*vec2.y - vec1.y*vec2.x;
        return ans;
    }

    static bool collinear(const Vector& vec1, const Vector& vec2)
    {
        assert(vec1.valid() && vec2.valid());
        Vector ans = vector_mult(vec1, vec2);
        return (is_equal(ans.x, 0) && is_equal(ans.y, 0) && is_equal(ans.z, 0));
    }
};

class Line
{
public:
    Vector direction;
    Point point;
};

class Plane
{
public:
    double A = NAN, B = NAN, C = NAN, D = NAN;
    Vector norm;

    Plane(const Point& fst, const Point& snd, const Point& thd) : 
    A((snd.y - fst.y)*(thd.z - fst.z) - (thd.y - fst.y)*(snd.z - fst.z)), 
    B((thd.x - fst.x)*(snd.z - fst.z) - (snd.x - fst.x)*(thd.z - fst.z)),
    C((snd.x - fst.x)*(thd.y - fst.y) - (thd.x - fst.x)*(snd.y - fst.y)),
    D(-A*fst.x -B*fst.y -C*fst.z),
    norm(A, B, C) {}

    bool valid() const
    {
        return (std::isfinite(A) && std::isfinite(B) && std::isfinite(C) && std::isfinite(D));
    }

    void print() const
    {
        std::cout << "A = " << A << " B = " << B << " C = " << C << " D = " << D;
        std::cout << " Normal vector = ";
        norm.print();
    }
};
