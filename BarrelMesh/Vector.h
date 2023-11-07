#pragma once
#include "Point.h"
#include <math.h>
class Vector
{
public:
	Vector(const Point& point);
	Vector(float x = 0, float y = 0, float z = 0);
	Vector operator-(const Vector& v);
	Vector operator*(const Vector& v);
	float dot(const Vector& v);
	float length();
	float magnitude();
	float x() const;
	float y() const;
	float z() const;
	static Vector normal(const Point &a, const Point &b, const Point &c);
private:
	Point point;
};

