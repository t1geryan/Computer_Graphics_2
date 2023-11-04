#pragma once
#include"Matrix.h"

class AffineTransform {
public:
	static Matrix<double> Translation(double x, double y)
	{
		double T[3][3] = {
			{1, 0, x},
			{0, 1, y },
			{0, 0, 1 }
		};
		return Matrix<double>(3, 3, T);
	}

	static Matrix<> Identity()
	{
		double I[3][3] = {
			{1, 0, 0},
			{0, 1, 0 },
			{0, 0, 1 }
		};
		return Matrix<>(3, 3, I);
	}

	static Matrix<double> Scaling(double kx, double ky)
	{
		double S[3][3] =
		{
			{kx, 0, 0},
			{0, ky, 0},
			{0, 0, 1},
		};
		return Matrix<double>(3, 3, S);
	}

	static Matrix<double> Rotation(double angle)
	{
		double c = cos(angle), s = sin(angle);

		double R[3][3] =
		{
			{c, s, 0},
			{-s, c, 0},
			{0, 0, 1}
		};
		return Matrix<double>(3, 3, R);
	}

	static Matrix<double> ReflectOX()
	{
		return Scaling(1, -1);
	}

	static Matrix<double> ReflectOY()
	{
		return Scaling(-1, 1);
	}

	static Matrix<double> ReflectAll()
	{
		return Scaling(-1, -1);
	}
};
