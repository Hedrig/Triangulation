#pragma once
#include <vector>
#include "Point.h"
#include "Vector.h"
#include <math.h>
class Circumsphere
{
public:
	Circumsphere(const std::vector<Point> points);
	bool hasInside(const Point& point) const;
private:
	std::vector<Point> pts;
	float a, dx, dy, dz, c;
	Point center;
	float r;
	float det3(std::vector<Vector> m);
};

