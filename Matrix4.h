#pragma once
#include <cmath>
#include "Vec3.h"

class Matrix4
{
public:
	float data[4 * 4];

	float& el(int x, int y)
	{
		return data[x + 4 * y];
	}
	const float& el(int x, int y) const
	{
		return data[x + 4 * y];
	}

	Matrix4()
	{
		for (int x = 0; x < 4; x++)
			for (int y = 0; y < 4; y++)
				el(x, y) = x == y ? 1 : 0;
	}

	Vec3 operator *(const Vec3& p)
	{
		return Vec3(
			el(0, 0) * p.x + el(1, 0) * p.y + el(2, 0) * p.z + el(3, 0) * 1,
			el(0, 1) * p.x + el(1, 1) * p.y + el(2, 1) * p.z + el(3, 1) * 1,
			el(0, 2) * p.x + el(1, 2) * p.y + el(2, 2) * p.z + el(3, 2) * 1
		);
	}

	Matrix4 operator *(const Matrix4& m)
	{
		return Matrix4(); //TODO
	}


	static Matrix4 translate(const Vec3& position)
	{
		Matrix4 ret;
		ret.el(3, 0) = position.x;
		ret.el(3, 1) = position.y;
		ret.el(3, 2) = position.z;
		return ret;
	}

	static Matrix4 rotate(float angle, Vec3 axis)
	{
		Matrix4 m;
		float a = angle;
		float c = (float)std::cos(a);
		float s = (float)std::sin(a);

		axis = axis.normalized();

		Vec3 temp = axis * (1 - c);

		m.el(0, 0) = c + temp.x * axis.x;
		m.el(0, 1) = 0 + temp.x * axis.y + s * axis.z;
		m.el(0, 2) = 0 + temp.x * axis.z - s * axis.y;

		m.el(1, 0) = 0 + temp.y * axis.x - s * axis.z;
		m.el(1, 1) = c + temp.y * axis.y;
		m.el(1, 2) = 0 + temp.y * axis.z + s * axis.x;

		m.el(2, 0) = 0 + temp.z * axis.x + s * axis.y;
		m.el(2, 1) = 0 + temp.z * axis.y - s * axis.x;
		m.el(2, 2) = c + temp.z * axis.z;
		m.el(3, 3) = 1;
		return m;
	}

};