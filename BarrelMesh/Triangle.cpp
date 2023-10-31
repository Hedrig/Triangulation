#include "Triangle.h"

Triangle::Triangle(const Point &a, const Point &b, const Point &c)
    : p_a{ a }, p_b{ b }, p_c{ c }
{
    createEdges();
}

Triangle::Triangle(const std::vector<Point> &points)
{
    p_a = points[0];
    p_b = points[1];
    p_c = points[2];
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

void Triangle::createEdges()
{
    p_edges = std::vector<Edge>{ 
        Edge(p_a, p_b),
        Edge(p_b, p_c),
        Edge(p_c, p_a) };
}
