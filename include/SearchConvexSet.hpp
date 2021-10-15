#ifndef SEARCH_CONVEX_SET_HPP
#define	SEARCH_CONVEX_SET_HPP

#include <vector>
#include <algorithm>
#include <set>
#include <exception>
#include <iostream>
#include<bits/stdc++.h>

#include "DataTypes.hpp"
#include "Point.hpp"


class SearchConvexSet
{
	public:
		std::set<point::Point>		searchPoints(std::vector<point::Point>& points);
		void						printConvexSetPoints();

	private:
		std::vector<point::Point>	pointsOutside; // точки снаружи
		std::vector<point::Point>	setOfPoints; // множество точек, над которыми будут проводиться операции
		std::set<point::Point>		convexSetPoints; // множество точек, принадлежащих контуру выпуклой фигуре

		int							findSide(point::Point a, point::Point b, point::Point pointOutside);
		void						findHull(std::vector<point::Point>& points, point::Point& start, point::Point& end, int side);
		std::vector<double>			calculateHyperplane(point::Point a, point::Point b);
		double						equationHyperplane(point::Point a, const std::vector<double>&	coeffHyperplane);
		std::vector<point::Point>	searchMinMaxPoints(std::vector<point::Point>& points, char axesMinMax = 'x');
		void						printSetOfPoints();
};

#endif