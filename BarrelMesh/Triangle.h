#pragma once
#include "Point.h"
#include <iterator>
#include <vector>
#include <list>

#include "Edge.h"
#include "Vector.h"

class Triangle
{
public:
	Triangle(const Point &a = Point(), const Point &b = Point(), const Point &c = Point());
	Triangle(const std::vector<Point> &points);
	Point a() const;
	Point b() const;
	Point c() const;
	std::vector<Edge> edges();
	bool isVisible(const Point& point) const;
	bool isOnPlane(const Point& point) const;
	bool operator==(const Triangle& t) const
	{
		return p_a == t.p_a && p_b == t.p_b && p_c == t.p_c;
	};
private:
	Vector p_normal;
	Point p_a, p_b, p_c;
	std::vector<Edge> p_edges;
	void createEdges();
	void reorderPoints();
};

template <>
struct std::hash<Triangle>
{
	// Оба простых числа выбраны произвольно
	static const int M = 100003, n = 50021;
	std::size_t operator ()(const Triangle& value) const
	{
		int a = value.a().index(), b = value.b().index(), c = value.c().index();
		return static_cast<size_t>((a * a * n + b * n + c) % M);
	}
};