#pragma once
#include "Point.h"
struct Edge
{
public:
	Edge(Point a = Point(), Point b = Point())
		: a{ a }, b{ b } {};
	Point a;
	Point b;
	bool operator==(Edge& e) const { 
		return	this->a == e.a && this->b == e.b || 
				this->a == e.b && this->b == e.a;
	};
};

