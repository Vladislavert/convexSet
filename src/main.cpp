#include "SearchConvexSet.hpp"
#include "Point.hpp"
#include <fstream>
// #include "draw.hpp"

const unsigned int	QUANTITY_POINTS = 5; // кол-во точек

int	saveInFile(const char* fileName, const std::vector<point::Point>& points)
{
	std::ofstream file(fileName);

	file.clear();
	for	(unsigned int i = 0; i < points.size(); i++)
		file << points[i].x << " ";
	file << std::endl;
	for	(unsigned int i = 0; i < points.size(); i++)
		file << points[i].y << " ";
	file.close();
}

int	saveInFile(const char* fileName, const std::set<point::Point>& points)
{
	std::ofstream file(fileName);

	file.clear();
	for (std::set<point::Point>::iterator it = points.begin(); it != points.end(); it++)
		file << it->x << " ";
	file << std::endl;
	for (std::set<point::Point>::iterator it = points.begin(); it != points.end(); it++)
		file << it->y << " ";
	file.close();
}

int main()
{
	SearchConvexSet	searchConvexSet;

	std::vector<point::Point>	points(QUANTITY_POINTS);
	std::set<point::Point>		resPoints;
	

	points.push_back(point::Point(0, 0));

	points.push_back(point::Point(0, 2));

	points.push_back(point::Point(2, 2));

	points.push_back(point::Point(2, 0));

	points.push_back(point::Point(1, 1));

	points.push_back(point::Point(-1, -1));

	resPoints = searchConvexSet.searchPoints(points);

	saveInFile("points", points);
	saveInFile("points_res", resPoints);

	return (0);
}