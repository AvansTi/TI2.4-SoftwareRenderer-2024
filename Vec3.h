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
};

