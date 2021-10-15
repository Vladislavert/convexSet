#ifndef POINT_HPP
#define POINT_HPP

#pragma pack(push,1)

namespace point
{
	class Point
	{
		public:
			double	x;
			double	y;
			Point() {}
			Point(double x, double y) : x(x), y(y) {}
			bool	operator==(const Point& point)
			{
				return (x == point.x && y == point.y);
			}
			bool	operator==(const Point& point) const
			{
				return (x == point.x && y == point.y);
			}
			bool	operator<(const Point& point) const
			{
				return (x < point.x && y < point.y);
			}
			bool	operator>(const Point& point) const
			{
				return (x > point.x && y > point.y);
			}
	};
	bool	compareX(const point::Point& point1, const point::Point& point2);
	bool	compareY(const point::Point& point1, const point::Point& point2);
};

#pragma pack(pop)

#endif