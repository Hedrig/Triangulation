#include "Point.h"


Point::Point(int i, float x, float y, float z)
    :p_i{ i }, p_x{ x }, p_y{ y }, p_z{ z }
{}

Point::Point(float x, float y, float z)
    :p_i{ 0 }, p_x{ x }, p_y{ y }, p_z{ z }
{}

float Point::x() const
{
    return p_x;
}


float Point::y() const 
{
    return p_y;
}


float Point::z() const
{
    return p_z;
}


int Point::index() const
{
    return p_i;
}
