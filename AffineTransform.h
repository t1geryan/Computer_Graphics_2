#include"Matrix.h"
#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

Matrix<> Translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1 };
	return Matrix<double>(3, 3, T);
}

Matrix<> Identity()
{
	double I[9] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1 };
	return Matrix<double>(3, 3, I);
}


#endif AFFINE_TRANSFORM_H
