#pragma once
#include "Point.h"
#include "Edge.h"

class Triangle
{
public:
	Triangle(Point a = Point(), Point b = Point(), Point c = Point());
	Point a();
	Point b();
	Point c();
private:
	Point p_a, p_b, p_c;
	Edge ab, bc, ca;
};

