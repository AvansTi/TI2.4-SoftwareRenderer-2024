#pragma once
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
};

