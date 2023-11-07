#pragma once
#include "Triangle.h"
#include "Circumsphere.h"
#include <vector>
class Tetrahedron
{
public:
	Tetrahedron(const Point &a = Point(), const Point& b = Point(), const Point& c = Point(), const Point& d = Point());
	Tetrahedron(Triangle &t, const Point& a = Point());
	Tetrahedron(const std::vector<Triangle>& triangles);
	Tetrahedron(const std::vector<Point>& points);
	std::vector<Triangle> &triangles();
	bool inCircumsphere(const Point& point) const;
	bool operator==(const Tetrahedron& t) const;
private:
	std::vector<Triangle> p_triangles;
    std::vector<Point> p_points;
	Circumsphere circumsphere;
};

