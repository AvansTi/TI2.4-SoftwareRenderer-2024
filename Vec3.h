#pragma once
class Vec3
{
public:
	union
	{
		float data[3];
		struct
		{
			float x;
			float y;
			float z;
		};
	};

	Vec3(float x, float y, float z);
	Vec3();

	Vec3 normalized();

	Vec3 cross(const Vec3& other) const;
	float dot(const Vec3& other) const;

	Vec3 operator + (const Vec3& other) const;
	Vec3 operator - (const Vec3& other) const;
	Vec3 operator * (const Vec3& other) const;
	Vec3 operator * (float other) const;
};

