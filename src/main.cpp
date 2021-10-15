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

	saveInFile("points", points);

	// Plot	plot;

	// std::vector<double>	coordinateX;
	// std::vector<double>	coordinateY;

	// for (uint_t i = 0; i < points.size(); i++)
	// {
	// 	coordinateX.push_back(points[i].x);
	// 	coordinateY.push_back(points[i].y);
	// }
	
	// // drawGraph(&coordinateX, &coordinateY, &plot, "set", 0);
    // plot.drawBrokenCurveWithPoints(coordinateX, coordinateY).label("broken lines");
	// plot.grid().show();
	// plot.show();
	return (0);
}