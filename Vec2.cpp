#include "Vec2.h"
#include "Vec3.h"

Vec2::Vec2(float x, float y) : x(x), y(y)
{
}

Vec2::Vec2(const Vec3& v) : x(v.x), y(v.y)
{
}

Vec2 Vec2::operator+(const Vec2& other) const
{
	return Vec2(x + other.x, y + other.y);
}
Vec2 Vec2::operator-(const Vec2& other) const
{
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(const Vec2& other) const
{
	return Vec2(x*other.x, y*other.y);
}

Vec2 Vec2::operator*(float other) const
{
	return Vec2(x*other, y*other);
}
