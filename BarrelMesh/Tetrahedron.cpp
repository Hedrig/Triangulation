#include "Tetrahedron.h"

Tetrahedron::Tetrahedron(const Point& a, const Point& b, const Point& c, const Point& d)
    :p_triangles{ Triangle(a, b, c), Triangle(a, c, d), Triangle(d, b, a), Triangle(d, c, b), },
     p_points{ a,b,c,d }, circumsphere(p_points)
{}

Tetrahedron::Tetrahedron(Triangle& t, const Point& a)
    :p_triangles{ t, Triangle(t.a(), t.b(), a), Triangle(a, t.c(), t.a()), Triangle(t.b(), t.c(), a)},
    p_points{ t.a(), t.b(), t.c(), a }, circumsphere(p_points)
{}

Tetrahedron::Tetrahedron(const std::vector<Point>& points)
    :Tetrahedron(points[0], points[1], points[2], points[3])
{}

std::vector<Triangle> &Tetrahedron::triangles()
{
    return p_triangles;
}

bool Tetrahedron::inCircumsphere(const Point& point) const
{
    return circumsphere.hasInside(point);
}

bool Tetrahedron::operator==(const Tetrahedron& t) const
{
    return p_points == t.p_points;
}

