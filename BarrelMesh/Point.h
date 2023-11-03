#pragma once
struct Point
{
public:
	Point(int i, float x, float y, float z);
	Point(float x = 0, float y = 0, float z = 0);
	float x() const;
	float y() const;
	float z() const;
	int index() const;
	bool operator==(const Point& p) const {
		return this->p_x == p.p_x && this->p_y == p.p_y && this->p_z == p.p_z;
	}
	// Для сортировки в лексиграфическом порядке
	bool operator<(const Point& p) const {
		return this->p_x < p.p_x
			|| this->p_x == p.p_x && this->p_y < p.p_y
			|| this->p_x == p.p_x && this->p_y == p.p_y && this->p_z < p.p_z;
	}
private:
	int p_i;
	float p_x, p_y, p_z;
};