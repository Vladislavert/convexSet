#include <vector>
#include <algorithm>
#include <set>

#include "MessageSender.hpp"
#include "DataTypes.hpp"
#include "Point.hpp"


#define DEBUG

#ifdef DEBUG
	#include <iostream>
#endif

// поля структуры

std::vector<Point>	pointsOutside; // точки снаружи
std::vector<Point>	setOfPoints; // множество точек, принадлежащих контуру выпуклой фигуре

#define	EPS 0.00001 // коэффициент, для сравнения double



const unsigned int	QUANTITY_POINTS = 5; // кол-во точек
const unsigned int	QUANTITY_POINTS_1 = 4; // кол-во точек

bool				compareX(const Point& point1, const Point& point2)
{
	return (point1.x < point2.x);
}

bool				compareY(const Point& point1, const Point& point2)
{
	return (point1.y < point2.y);
}

// rename
void				setIndexExtremePoints(std::vector<Point>& sortPoints, const std::vector<Point>& points,
										  std::vector<uint_t>& indexExtremePoints, bool compare(const Point&, const Point&))
{
	std::sort(sortPoints.begin(), sortPoints.end(), compare);
	indexExtremePoints.push_back(std::find(points.cbegin(), points.cend(), sortPoints[0])		- points.cbegin());
	indexExtremePoints.push_back(std::find(points.cbegin(), points.cend(), sortPoints.back())	- points.cbegin());
}

/**
 * @brief поиск крайних точек
 * 
 * @param points точки
 * @return индексы крайних точек
 */
std::vector<uint_t>	searchExtremePoints(const std::vector<Point>& points)
{
	std::vector<uint_t>	indexExtremePoints;
	std::vector<Point>	sortPoints(points);

	setIndexExtremePoints(sortPoints, points, indexExtremePoints, compareX);
	setIndexExtremePoints(sortPoints, points, indexExtremePoints, compareY);

	return (indexExtremePoints);
}

// bool	

/**
 * @brief Поиск барицентра фигуры
 * 
 * @return координаты барицентра 
 */
Point					searchBarycenter()
{
	Point	resBarycenter;
	Point	sum;

	sum.x = 0;
	sum.y = 0;
	for	(uint_t i = 0; i < setOfPoints.size(); i++)
	{
		sum.x += setOfPoints[i].x;
		sum.y += setOfPoints[i].y;
	}
	resBarycenter.x = sum.x / setOfPoints.size();
	resBarycenter.y = sum.y / setOfPoints.size();

	return (resBarycenter);
}

// переименовать
/**
 * @brief рассчитывает уравнение нормали, проходящей через
 * 		  точку pointOutside и прямой проходящей через точки a и b
 * 
 * @param a координаты первой точки, принадлежащей прямой
 * @param b координаты второй точки, принадлежащей прямой
 * @param pointOutside точка, не принадлежащая прямой, через которую проходит
 * 					   нормаль
 * @return уравнение вида y = k*x + b
 * Результат вектор коэфф. уравнения k, b
 */
std::vector<double>	calculateLineNormal(Point a, Point b, Point pointOutside)
{
	std::vector<double>	resCoeff(2);
	// (x - a.x)*(b.y-a.y) = (y - a.y)*(b.x - a.x)
	// x(b.y - a.y) - a.x(b.y - a.y) + y(-b.x + a.x) + a.y(-b.x + a.x)

	// поиск уравнения нормали

	// 	   		  (-b.x + a.x)
	// y_0	-  (- -------------) (x - x_0)
	//     		  (b.y - a.y)
	// , где x_0, y_0 - точка не принадлежащая прямой(pointOutside)

	if (((b.y - a.y) < EPS) || ((-b.x + a.x) < EPS))
	{
		resCoeff[0] = 0;
		resCoeff[1] = pointOutside.y;
	}
	else
	{
		resCoeff[0] = (b.x - a.x) / (b.y - a.y);
		resCoeff[1] = pointOutside.y - ((b.x - a.x) / (b.y - a.y)) * (-pointOutside.x);
	}

	return (resCoeff);
}



// Point			calculateIntersect()
// {
// 	Point resIntersect;


// }


// расчёт уравнения прямой, которая является гиперплоскостью
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
std::vector<double>	calculateHyperplane(Point a, Point b, Point pointOutside)
{
	std::vector<double> normal;
	std::vector<double>	resCoeffHyperplane(3);

	normal = calculateLineNormal(a, b, pointOutside);
	resCoeffHyperplane[0] = 1;
	resCoeffHyperplane[1] = normal[0];

	// 1(x - a.x) + k(y - a.y) = 0
	// b = -a.x + k*(-a.y)

	resCoeffHyperplane[2] = -a.x + normal[0] * (-a.y); 

	return (resCoeffHyperplane);
}

double			equationHyperplane(Point a, std::vector<double>	coeffHyperplane)
{
	return (coeffHyperplane[0]*a.x + coeffHyperplane[1]*a.y + coeffHyperplane[2]);
}

/**
 * @brief поиск внутренних точек
 * 
 * @param points 
 * @param indexExtremePoints 
 * @return std::vector<itPoint_t> 
 */
std::vector<itPoint_t>	searchInsidePoints(const std::vector<Point>& points, std::vector<uint_t> indexExtremePoints)
{
	std::vector<itPoint_t>	resInsidePoints;
	std::vector<double>		coeffHyperplane;
	double					valueHyperplane;
	bool					isInside;

	// coeffHyperplane = calculateHyperplane(points[0], points[1], searchBarycenter());

	// double test = equationHyperplane(points[3], coeffHyperplane);

	isInside = 1;
	for (uint_t i = 0; i < points.size() - 1; i++)
	{
		coeffHyperplane = calculateHyperplane(points[i], points[i + 1], searchBarycenter());
		valueHyperplane = equationHyperplane(searchBarycenter(), coeffHyperplane);
		isInside *= (valueHyperplane >= 0);
	}
	

	return (resInsidePoints);
}


std::vector<Point>	deletePoints(const std::vector<Point>& points)
{
	std::vector<Point>	newPoints;
	std::vector<uint_t>	indexExtremePoints;
	Point				coordinateBarycenter;
	std::set<uint_t>	setOfIndex; // не повторяющие		

	// функция должна возврашаеть setOfPoints заполненные(НЕ ИНДЕКС!!!)
	indexExtremePoints = searchExtremePoints(points);
	setOfIndex = std::set<uint_t>(indexExtremePoints.begin(), indexExtremePoints.end());

	indexExtremePoints.clear();
	std::copy(setOfIndex.begin(), setOfIndex.end(), std::back_inserter(indexExtremePoints));
	for (size_t i = 0; i < indexExtremePoints.size(); i++)
	{
		setOfPoints.push_back(points[indexExtremePoints[i]]); // отрефакторить
	}

	coordinateBarycenter = searchBarycenter();
	
	// запуск поиска точек, которые находятся внутри

	searchInsidePoints(setOfPoints, indexExtremePoints);
	

	#ifdef DEBUG
		for (size_t i = 0; i < indexExtremePoints.size(); i++)
		{
			std::cout << indexExtremePoints[i] << " ";
		}
		std::cout << std::endl;
	#endif


	return(points);
}


int main()
{
	std::vector<Point>	points(QUANTITY_POINTS);
	// Point*	newPoints;

	MessageSender messageSender;

	points[0].x = 0;
	points[0].y = 0;

	points[1].x = 0;
	points[1].y = 2;

	points[2].x = 2;
	points[2].y = 2;

	points[3].x = 2;
	points[3].y = 0;

	points[4].x = 1;
	points[4].y = 1;


	deletePoints(points);


	// while(true)
	// {
	// 	messageSender.send(points, points_1, QUANTITY_POINTS, QUANTITY_POINTS);
	// }


	// delete[] newPoints;

	return (0);
}