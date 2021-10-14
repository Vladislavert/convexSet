#include "Point.hpp"

bool	point::compareX(const point::Point& point1, const point::Point& point2)
{
	return (point1.x < point2.x);
}

bool	point::compareY(const point::Point& point1, const point::Point& point2)
{
	return (point1.y < point2.y);
}