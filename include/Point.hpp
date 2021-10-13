#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#pragma pack(push,1)

struct Point
{
	double	x;
	double	y;
	bool	operator==(const Point& point)
	{
		return (x == point.x && y == point.y);
	}
	bool	operator==(const Point& point) const
	{
		return (x == point.x && y == point.y);
	}
};

#pragma pack(pop)

#endif