#include "Edge.h"

Edge::Edge(const Point &a, const Point &b)
    : p_a{ a }, p_b{ b } { }

Point Edge::a()
{
    return p_a;
}

Point Edge::b()
{
    return p_b;
}

float Edge::distance(const Point& c)
{
    Vector A(p_a), B(p_b), C(c),
           AB = B - A,
           AC = C - A;
    return (AB * AC).magnitude() / AB.magnitude();
}
