#ifndef MATH_LINE_HPP
#define	MATH_LINE_HPP

// #include <Eigen/Dense>
#include "Point.hpp"

class MathLine()
{
	public:
		Eigen::Matrix2d	parametricOfSstraightLine(Point x1, Point x2);
		Point			calcualteDirectionVector();

	private:
};

#endif