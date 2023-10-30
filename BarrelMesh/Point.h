#pragma once
struct Point
{
public:
	Point(int i = 0, float x, float y, float z);
	float x() const;
	float y() const;
	float z() const;
	int index();
	bool operator==(const Point& p) const {
		return this->p_x == p.p_x && this->p_y == p.p_y && this->p_z == p.p_z;
	}
private:
	int p_i;
	float p_x, p_y, p_z;
};