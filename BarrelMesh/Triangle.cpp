#include "Triangle.h"

Triangle::Triangle(Point a, Point b, Point c)
    : p_a{ a }, p_b{ b }, p_c{ c }
{
    ab = Edge(a, b);
    bc = Edge(b, c);
    ca = Edge(c, a);
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
