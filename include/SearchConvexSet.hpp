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
		// SearchConvexSet();

		std::set<point::Point>		searchPoints(std::vector<point::Point>& points);
		void						findHull(std::vector<point::Point>& points, point::Point& start, point::Point& end, int side);
		void						printConvexSetPoints();
		// ~SearchConvexSet();
	private:
		std::vector<point::Point>	pointsOutside; // точки снаружи
		std::vector<point::Point>	setOfPoints; // множество точек, над которыми будут проводиться операции
		std::set<point::Point/*std::pair<int, int>*/>		convexSetPoints; // множество точек, принадлежащих контуру выпуклой фигуре

		// std::vector<double>	calculateHyperplane(point::Point a, point::Point b, point::Point pointOutside);
		int					findSide(point::Point a, point::Point b, point::Point pointOutside);
		std::vector<double>	calculateLineNormal(const point::Point& a, const point::Point& b, const point::Point& pointOutside);
		std::vector<double>	calculateHyperplane(point::Point a, point::Point b);
		double				equationHyperplane(point::Point a, const std::vector<double>&	coeffHyperplane);
		void				setIndexExtremePoints(std::vector<point::Point>& sortPoints, const std::vector<point::Point>& points,
										  		  std::vector<uint_t>& indexExtremePoints, bool compare(const point::Point&, const point::Point&));
		std::vector<point::Point>	searchMinMaxPoints(std::vector<point::Point>& points, char axesMinMax = 'x');
		std::vector<uint_t>	searchIndexMinMaxPoints(const std::vector<point::Point>& points, char axesMinMax);
		void				clearPointsOutside(const std::vector<point::Point>& interiorPoints);

		void				printSetOfPoints();
};

#endif