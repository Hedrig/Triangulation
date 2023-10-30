#pragma once
#include "Point.h"
#include <math.h>
class Vector
{
public:
	Vector(const Point& point = Point());
	Vector(float x = 0, float y = 0, float z = 0);
	Vector operator-(const Vector& v);
	Vector operator*(const Vector& v);
	float magnitude();
	float x() const;
	float y() const;
	float z() const;
private:
	Point point;
};

