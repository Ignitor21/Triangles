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

namespace geometry
{

class Point
{
public:

    double x = NAN, y = NAN, z = NAN;

    Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    Point() {}

    void print() const
    {
        std::cout << "(" << x << ";" << y << ";" << z << ")"; 
    }

    bool valid() const
    {
        return (std::isfinite(x) && std::isfinite(y) && std::isfinite(z));
    }

    bool operator == (const Point &rhs) const
    {
        if (!valid() || !rhs.valid())
            return false;
        return (is_equal(x, rhs.x) && is_equal(y, rhs.y) && is_equal(z, rhs.z));
    }
};

class Vector
{
public:
    double x = NAN, y = NAN, z = NAN;

    Vector(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    Vector(const Point& point) : x(point.x), y(point.y), z(point.z) {}
    Vector(const Point& point1, const Point& point2) : x(point2.x - point1.x), y(point2.y - point1.y), z(point2.z - point1.z) {}
    Vector() {}

    void print() const
    {
        std::cout << "(" << x << ";" << y << ";" << z << ")"; 
    }

    bool valid() const
    {
        return (std::isfinite(x) && std::isfinite(y) && std::isfinite(z));
    }

    bool null() const
    {
        return is_equal(x, 0) && is_equal(y, 0) && is_equal(z, 0);
    }

    double length() const
    {
        assert(valid());
        return std::sqrt(x*x + y*y + z*z);
    }

    bool operator ==(const Vector& rhs) const
    {
        if (!valid() || !rhs.valid())
            return false;
        return (is_equal(x, rhs.x) && is_equal(y, rhs.y) && is_equal(z, rhs.z));
    }

    Vector operator- () const
    {
        return Vector{-x, -y, -z};
    }
};

Vector operator * (const double& number, const Vector& vec)
{
    return Vector{vec.x * number, vec.y * number, vec.z * number};
}

Vector operator * (const Vector& vec, const double& number)
{
    return number * vec;
}

Vector operator + (const Vector& vec1, const Vector& vec2)
{
    return Vector{vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z};
}

Vector operator - (const Vector& vec1, const Vector& vec2)
{
    return Vector{vec1.x - vec2.x, vec1.y - vec2.y, vec2.z - vec1.z};
}

Vector vector_mult(const Vector& vec1, const Vector& vec2)
{
    assert(vec1.valid() && vec2.valid());
    Vector ans;
    ans.x = vec1.y*vec2.z - vec1.z*vec2.y;
    ans.y = vec1.z*vec2.x - vec1.x*vec2.z;
    ans.z = vec1.x*vec2.y - vec1.y*vec2.x;
    return ans;
}

bool collinear(const Vector& vec1, const Vector& vec2)
{
    assert(vec1.valid() && vec2.valid());
    Vector ans = vector_mult(vec1, vec2);
    return (is_equal(ans.x, 0) && is_equal(ans.y, 0) && is_equal(ans.z, 0));
}

double scalar_mult(const Vector& vec1, const Vector& vec2)
{
    assert(vec1.valid() && vec2.valid());
    return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z); 
}

class Line
{
public:
    Vector direction;
    Point point;

    Line(const Vector& dir, const Point& p) : direction(dir), point(p) {}
    Line() {}

    bool point_belongs(const Point& p) const
    {
        assert(p.valid());
        Vector new_vec{p , point};
        return collinear(direction, new_vec);
    }

    bool valid() const
    {
        return (direction.valid() && point.valid());
    }

    void print() const
    {
        std::cout << "Line: Direction vector: ";
        direction.print();
        std::cout << " ";
        std::cout << "Point: ";
        point.print();
    }

    bool operator ==(const Line& line)
    {
        if (!valid() || !line.valid())
            return false;
        return (direction == line.direction && point == line.point);
    }
};

class Plane
{
public:
    double A = NAN, B = NAN, C = NAN, D = NAN;
    Vector norm;

    Plane(const Point& fst, const Point& snd, const Point& thd) : 
    A((snd.y - fst.y)*(thd.z - fst.z) - (thd.y - fst.y)*(snd.z - fst.z)), 
    B((thd.x - fst.x)*(snd.z - fst.z) - (snd.x - fst.x)*(thd.z - fst.z)),
    C((snd.x - fst.x)*(thd.y - fst.y) - (thd.x - fst.x)*(snd.y - fst.y))
    {
        double factor = 1/std::sqrt(A*A + B*B + C*C);
        A *= factor;
        B *=factor;
        C *= factor;
        D = -A*fst.x -B*fst.y -C*fst.z;
        norm = Vector{A, B, C};
    }

    bool valid() const
    {
        return (std::isfinite(A) && std::isfinite(B) && std::isfinite(C) && std::isfinite(D) && norm.valid());
    }

    void print() const
    {
        std::cout << "A = " << A << " B = " << B << " C = " << C << " D = " << D;
        std::cout << " Normal vector = ";
        norm.print();
    }

    double find_halfspace(const Point& point) const
    {
        return A*point.x + B*point.y + C*point.z + D;
    }
};

Line plane_intersection(const Plane& plane1, const Plane& plane2)
{
    assert(plane1.valid() && plane2.valid());
    Vector dir = vector_mult(plane1.norm, plane2.norm);
    Line ans;

    if (dir.null())
    {
        if(((plane1.norm == -plane2.norm) && is_equal(-plane1.D, plane2.D)) || is_equal(plane1.D, plane2.D))
        {
            ans.direction = dir;
        }

        return ans;
    }

    double s1 = -plane1.D;
    double s2 = -plane2.D;
    double n1n2dot = scalar_mult(plane1.norm, plane2.norm);
    double n1normsqr = scalar_mult(plane1.norm, plane1.norm);
    double n2normsqr = scalar_mult(plane2.norm, plane2.norm);
    double a = (s2 * n1n2dot - s1 * n2normsqr)/(n1n2dot * n1n2dot - n1normsqr * n2normsqr);
    double b = (s1 * n1n2dot - s2 * n2normsqr)/(n1n2dot * n1n2dot - n1normsqr * n2normsqr);
    Vector vec_to_point = a*plane1.norm + b*plane2.norm;
    ans.point.x = vec_to_point.x;
    ans.point.y = vec_to_point.y;
    ans.point.z = vec_to_point.z;
    ans.direction = dir;
    return ans;
}

class Triangle
{
public:
    std::vector<Point> verticies;

    Triangle(const Point& p1, const Point& p2, const Point& p3)
    {
        verticies.push_back(p1);
        verticies.push_back(p2);
        verticies.push_back(p3);
    }
};

bool triangles_intersection_2d(const Triangle& tr1, const Triangle& tr2)
{
    //TODO
    return true;
}

bool intervals_overlap(const Triangle& tr1, const Triangle& tr2, const Line&)
{
    //TODO
    return true;
}

bool triangles_intersection_3d(const Triangle& tr1, const Triangle& tr2)
{
    Plane plane1{tr1.verticies[0], tr1.verticies[1], tr1.verticies[2]};
    Plane plane2{tr2.verticies[0], tr2.verticies[1], tr2.verticies[2]};

    double half_space1 = plane2.find_halfspace(tr1.verticies[0]);
    double half_space2 = plane2.find_halfspace(tr1.verticies[1]);
    double half_space3 = plane2.find_halfspace(tr1.verticies[2]);

    if ((half_space1 > 0 && half_space2 > 0 && half_space3 > 0) || (half_space1 < 0 && half_space2 < 0 && half_space3 < 0))
        return false;

    Line intersection = plane_intersection(plane1, plane2);

    if (intersection.direction.null())
    {
        return triangles_intersection_2d(tr1, tr2);
    }

    return intervals_overlap(tr1, tr2, intersection);
    
}
}