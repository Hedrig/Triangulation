#include "Triangle.h"

Triangle::Triangle(const Point& a, const Point& b, const Point& c)
    : p_a{ a }, p_b{ b }, p_c{ c }, p_normal{ Vector::normal(a, b, c)}
{
    reorderPoints();
    createEdges();
}

Triangle::Triangle(const std::vector<Point>& points)
    :p_a{ points[0] }, p_b{ points[1] }, p_c{ points[2] },
     p_normal{ Vector::normal(points[0], points[1], points[2])}
{
    reorderPoints();
    createEdges(); 
}

Point Triangle::a() const
{
    return p_a;
}


Point Triangle::b() const
{
    return p_b;
}


Point Triangle::c() const
{
    return p_c;
}

std::vector<Edge> Triangle::edges()
{
    return p_edges;
}

bool Triangle::isVisible(const Point& point) const
{
    // Точка видима из этого треугольника, если треугольник обращён в сторону этой точки.
    return (Vector(p_a) - Vector(point)).dot(p_normal) < 0;
}

bool Triangle::isOnPlane(const Point& point) const
{
    // Точка лежит на плоскости треугольника, если её вектор перпендикулярен вектору нормали.
    return (Vector(p_a) - Vector(point)).dot(p_normal) == 0;
}

void Triangle::createEdges()
{
    p_edges = std::vector<Edge>{ 
        Edge(p_a, p_b),
        Edge(p_b, p_c),
        Edge(p_c, p_a) };
}

void Triangle::reorderPoints()
{
    if (p_a.index() > p_b.index())
        std::swap(p_a, p_b);
    if (p_a.index() > p_c.index())
        std::swap(p_a, p_c);
    if (p_b.index() > p_c.index())
        std::swap(p_b, p_c);
}
