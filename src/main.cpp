#include "SearchConvexSet.hpp"
#include "Point.hpp"

const unsigned int	QUANTITY_POINTS = 5; // кол-во точек

int main()
{
	SearchConvexSet	searchConvexSet;

	std::vector<point::Point>	points(QUANTITY_POINTS);
	

	points.push_back(point::Point(0, 0));

	points.push_back(point::Point(0, 2));

	points.push_back(point::Point(2, 2));

	points.push_back(point::Point(2, 0));

	points.push_back(point::Point(1, 1));

		points.push_back(point::Point(-1, -1));


	// deletePoints(points);


	searchConvexSet.searchPoints(points);

	return (0);
}