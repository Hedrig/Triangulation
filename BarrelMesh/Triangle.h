#pragma once
#include "Point.h"
#include <iterator>
#include <vector>
#include <list>
#include "Edge.h"

class Triangle
{
public:
	Triangle(const Point &a = Point(), const Point &b = Point(), const Point &c = Point());
	Triangle(const std::vector<Point> &points);
	Point a() const;
	Point b() const;
	Point c() const;
	std::vector<Edge> edges();
	bool operator==(const Triangle& t) const
	{
		return p_a == t.p_a && p_b == t.p_b && p_c == t.p_c
			|| p_a == t.p_b && p_b == t.p_c && p_c == t.p_a
			|| p_a == t.p_c && p_b == t.p_a && p_c == t.p_b;
	};
private:
	Point p_a, p_b, p_c;
	std::vector<Edge> p_edges;
	void createEdges();
};