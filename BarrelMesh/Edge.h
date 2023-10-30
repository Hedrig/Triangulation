#pragma once
#include "Point.h"
#include "Vector.h"

struct Edge
{
public:
	Edge(const Point &a = Point(), const Point &b = Point());
	Point a();
	Point b();
	bool operator==(const Edge& e) const { 
		return	this->p_a == e.p_a && this->p_b == e.p_b ||
				this->p_a == e.p_b && this->p_b == e.p_a;
	};
	float distance(const Point& c);
private:
	Point p_a, p_b;
};

