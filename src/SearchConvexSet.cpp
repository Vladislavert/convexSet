#include "SearchConvexSet.hpp"

// std::vector<point::Point>	SearchConvexSet::searchPoints(std::vector<point::Point>& points)
// {
// 	std::vector<point::Point>	minMaxPointsX;
// 	// std::vector<uint_t>			indexMinMaxPointsX;
// 	// std::vector<double>			coeffHyperplane;
// 	// std::vector<double>			pointsOverHyperplane;
// 	// double						pastDistance;
// 	// double						currentDistance;

// 	setOfPoints = points;

// 	// pointsOutside  = points;

// 	// // добавить точку в вектор convexSetPoints
// 	minMaxPointsX = searchMinMaxPoints(setOfPoints, 'x');


// 	findHull(points, minMaxPointsX[0], minMaxPointsX[1], 1);
// 	printConvexSetPoints();
// 	findHull(points, minMaxPointsX[0], minMaxPointsX[1], -1);
// 	std::cout << "-------------" << std::endl;
// 	printConvexSetPoints();


// 	return (convexSetPoints);
// }


std::vector<point::Point>	SearchConvexSet::searchPoints(std::vector<point::Point>& points)
{
	std::vector<point::Point>	minMaxPointsX;
	// std::vector<uint_t>			indexMinMaxPointsX;
	// std::vector<double>			coeffHyperplane;
	// std::vector<double>			pointsOverHyperplane;
	// double						pastDistance;
	// double						currentDistance;

	setOfPoints = points;

	// pointsOutside  = points;

	// // добавить точку в вектор convexSetPoints
	minMaxPointsX = searchMinMaxPoints(setOfPoints, 'x');

	// indexSidePoints.push_back(minMaxPointsX[0]);
	// indexSidePoints.push_back(minMaxPointsX[1]);

	
	findHull(points, minMaxPointsX[0], minMaxPointsX[1], 1);
	printConvexSetPoints();
	findHull(points, minMaxPointsX[0], minMaxPointsX[1], -1);
	std::cout << "-------------" << std::endl;
	printConvexSetPoints();


	return (convexSetPoints);
}

void	SearchConvexSet::printConvexSetPoints()
{
	for (uint_t i = 0; i < convexSetPoints.size(); i++)
	{
		std::cout << "x = " << convexSetPoints[i].x
				  << ", y = " << convexSetPoints[i].y
				  << std::endl;
	}
	
}

/**
 * @brief Функция для поиска стороны относительно прямой a b
 * 
 * @param a начало прямой
 * @param b конец прямой
 * @param pointOutside точка, расположение которой требуется найти
 * @return 1 - над прямой, -1 - под прямой, 0 = на прямой
 */
int			SearchConvexSet::findSide(point::Point a, point::Point b, point::Point pointOutside)
{
	std::vector<double>			coeffHyperplane;
	double						distance;

	coeffHyperplane = calculateHyperplane(a, b);
	distance = equationHyperplane(pointOutside, coeffHyperplane);
	if (distance > 0)
		return (1);
	else if (distance < 0)
		return (-1);
	else
		return (0);	
}			


// void		SearchConvexSet::findHull(std::vector<point::Point>& points, point::Point& start, point::Point& end, int side)
// {
// 	uint_t	indexSidePoints;



// 	indexSidePoints = searchIndexSidePoints(points, start, end, side);
// 	convexSetPoints.push_back(points[indexSidePoints])
	
// 	if (index == -1)
// 	{
// 		convexSetPoints.push_back(start);
// 		convexSetPoints.push_back(end);
// 		return ;
// 	}

// 	// findHull(points, points[index], start, -findSide(points[index], start, end));
// 	// findHull(points, points[index], end, -findSide(points[index], end, start));
// }

// uint_t		SearchConvexSet::searchIndexSidePoints(std::vector<point::Point>& points, point::Point& start, point::Point& end, int side)
// {
// 	uint_t				index;
// 	double				pastDistance;
// 	double				maxDistance;
// 	std::vector<double>	coeffHyperplane;
// 	int 				currentSide;


// 	index = -1;
// 	maxDistance = 0;
// 	coeffHyperplane = calculateHyperplane(start, end);
// 	for (uint_t i = 0; i < points.size(); i++)
// 	{
// 		pastDistance = equationHyperplane(points[i], coeffHyperplane);
// 		currentSide = findSide(start, end, points[i]);
// 		if ((currentSide == side) && (pastDistance > maxDistance))
// 		{
// 			index = i;
// 			maxDistance = pastDistance;
// 		}
// 	}

// 	return (index);
// }


void		SearchConvexSet::findHull(std::vector<point::Point>& points, point::Point& start, point::Point& end, int side)
{
	int		index;
	double	pastDistance;
	double	maxDistance;
	std::vector<double>			coeffHyperplane;
	int 		currentSide;

	index = -1;
	maxDistance = 0;
	coeffHyperplane = calculateHyperplane(start, end);
	for (uint_t i = 0; i < points.size(); i++)
	{
		pastDistance = equationHyperplane(points[i], coeffHyperplane);
		currentSide = findSide(start, end, points[i]);
		if ((currentSide == side) && (pastDistance > maxDistance))
		{
			index = i;
			maxDistance = pastDistance;
		}
	}
	
	if (index == -1)
	{
		convexSetPoints.push_back(start);
		convexSetPoints.push_back(end);

		return ;
	}

	findHull(points, points[index], start, -findSide(points[index], start, end));
	findHull(points, points[index], end, -findSide(points[index], end, start));
}

// ????переименовать переменные a и b, как минимальные и максимальные значения по оси????
/**
 * @brief Рассчёт уравнения гиперплоскости проходящей через две точки и нормалью к барицентру в виде 
 * 
 * @param a координаты первой точки
 * @param b координаты второй точки
 * @param pointOutside точка, не принадлежащая прямой, через которую проходит
 * 					   нормаль
 * @return уравнение вида w_1*x_1 + w_2*x_2 + b = 0
 * , где (w_1, w_2) - нормаль к прямой. Результат вектор коэфф. уравнения(w_1, w_2, b)
 */
std::vector<double>	SearchConvexSet::calculateHyperplane(point::Point a, point::Point b)
{
	std::vector<double>			resCoeffHyperplane(3);
	point::Point				direction;

	direction.x = b.x - a.x;
	direction.y = b.y - a.y;

	resCoeffHyperplane[0] = -direction.y;
	resCoeffHyperplane[1] = direction.x;
	resCoeffHyperplane[2] = direction.y * a.x - direction.x * a.y; 

	return (resCoeffHyperplane);
}

/**
 * @brief Уравнение гиперплоскости
 * 
 * @param a координаты точки
 * @param coeffHyperplane коэффициенты гиперплоскости
 * @return 
 */
double				SearchConvexSet::equationHyperplane(point::Point a, const std::vector<double>&	coeffHyperplane)
{
	return (coeffHyperplane[0]*a.x + coeffHyperplane[1]*a.y + coeffHyperplane[2]);
}

/**
 * @brief Поиск минимального и максимального значения по оси X/Y в множестве
 * 
 * @param points множество точек
 * @param axesMinMax ось, по которой проводится сравнение ('x' || 'y')
 * @return значение крайних точек по выбранной оси
 */
std::vector<point::Point>	SearchConvexSet::searchMinMaxPoints(std::vector<point::Point>& points, char axesMinMax)
{
	std::vector<point::Point>	resMinMaxPoints(2);

	if (axesMinMax == 'x' || axesMinMax == 'X')
	{
		std::sort(points.begin(), points.end(), point::compareX);
		resMinMaxPoints[0] = points[0];
		resMinMaxPoints[1] = points.back();
	}
	else if (axesMinMax == 'y' || axesMinMax == 'Y')
	{
		std::sort(points.begin(), points.end(), point::compareY);
		resMinMaxPoints[0] = points[0];
		resMinMaxPoints[1] = points.back();
	}
	else
		throw ("axesMinMax is not a valid value");

	return (resMinMaxPoints);
}


// rename
void				SearchConvexSet::setIndexExtremePoints(std::vector<point::Point>& sortPoints, const std::vector<point::Point>& points,
										  std::vector<uint_t>& indexExtremePoints, bool compare(const point::Point&, const point::Point&))
{
	std::sort(sortPoints.begin(), sortPoints.end(), compare);
	indexExtremePoints.push_back(std::find(points.cbegin(), points.cend(), sortPoints[0])		- points.cbegin());
	indexExtremePoints.push_back(std::find(points.cbegin(), points.cend(), sortPoints.back())	- points.cbegin());
}

/**
 * @brief Поиск минимального и максимального значения по оси X/Y в множестве
 * 
 * @param points множество точек
 * @param axesMinMax ось, по которой проводится сравнение ('x' || 'y')
 * @return значение крайних точек по выбранной оси 
 */
std::vector<uint_t>	SearchConvexSet::searchIndexMinMaxPoints(const std::vector<point::Point>& points, char axesMinMax)
{
	std::vector<uint_t>	resIndexExtremePoints;
	std::vector<point::Point>	sortPoints(points);

	if (axesMinMax == 'x' || axesMinMax == 'X')
		setIndexExtremePoints(sortPoints, points, resIndexExtremePoints, point::compareX);
	else if (axesMinMax == 'y' || axesMinMax == 'Y')
		setIndexExtremePoints(sortPoints, points, resIndexExtremePoints, point::compareY);
	else
		throw ("axesMinMax is not a valid value");

	return (resIndexExtremePoints);
}

/**
 * @brief функция для очистки внешних функций от внутренних
 * 
 * @param interiorPoints внутренние функции или принадлежащие лежащие на множестве
 */
void				SearchConvexSet::clearPointsOutside(const std::vector<point::Point>& interiorPoints)
{
	for (uint_t i = 0; i < interiorPoints.size(); i++)
	{
		pointsOutside.erase(std::find(pointsOutside.cbegin(), pointsOutside.cend(), interiorPoints[i]));
	}	
}