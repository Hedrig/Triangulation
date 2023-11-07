#include "Vector.h"

Vector::Vector(const Point &point)
    : point { point }
{}

Vector::Vector(float x, float y, float z)
    : point{ Point(x, y, z) }
{}

Vector Vector::operator-(const Vector& v)
{
    return Vector(x() - v.x(), y() - v.y(), z() - v.z());
}

Vector Vector::operator*(const Vector& v)
{
    return Vector(y() * v.z() - z() * v.y(),
                  -(x() * v.z() - z() * v.x()),
                  x() * v.y() - y() * v.x());
}

float Vector::magnitude()
{
    return (float)sqrt(length());
}

float Vector::x() const
{
    return point.x();
}

float Vector::y() const
{
    return point.y();
}

float Vector::z() const
{
    return point.z();
}

Vector Vector::normal(const Point& a, const Point& b, const Point& c)
{
    return (Vector(b) - Vector(a)) * (Vector(c) - Vector(a));
}

float Vector::dot(const Vector& v)
{
    return x() * v.x() + y() * v.y() + z() * v.z();
}

float Vector::length()
{
    return dot(*this);
}
