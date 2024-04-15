#pragma once

class Vec3;

class Vec2
{
public:
	union
	{
		float data[2];
		struct
		{
			float x;
			float y;
		};
	};

	Vec2(float x, float y);
	Vec2(const Vec3& v);

	Vec2 operator + (const Vec2& other) const;
	Vec2 operator - (const Vec2& other) const;
	Vec2 operator * (const Vec2& other) const;
	Vec2 operator * (float other) const;
};

