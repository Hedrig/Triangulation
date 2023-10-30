#include "Triangle.h"

Triangle::Triangle(const Point &a, const Point &b, const Point &c)
    : p_a{ a }, p_b{ b }, p_c{ c }
{
    createEdges();
}

template<typename Iter>
Triangle::Triangle(const Iter& begin, const Iter& end)
{
    std::vector<Point> points;
    while (begin != end)
        points.push_back(*begin++);
    p_a = points[0];
    p_b = points[1];
    p_c = points[2];
    createEdges();
}


Point Triangle::a()
{
    return p_a;
}


Point Triangle::b()
{
    return p_b;
}


Point Triangle::c()
{
    return p_c;
}

std::vector<Edge> Triangle::edges()
{
    return p_edges;
}

void Triangle::createEdges()
{
    p_edges = std::vector<Edge>{ Edge(p_a, p_b),Edge(p_b, p_c), Edge(p_c, p_a) };
}
