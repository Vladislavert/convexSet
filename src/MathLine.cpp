#include "MathLine.hpp"

Eigen::Matrix2d	MathLine::parametricOfSstraightLine(Point x1, Point x2)
{
	Eigen::Matrix2d	resCoeffLine;

	resCoeffLine[0] = x1.x;
	resCoeffLine[1] = x2.x - x1.x;
	resCoeffLine[2] = x1.y;
	resCoeffLine[3] = x2.y - x1.y;

	return (resCoeffLine);
}