#include <charconv>
#include <wtypes.h>
#include <vector>

struct vec4
{
	float x, y, z, w;
};

struct vec3
{
	float x, y, z;

	vec3 operator-(vec3 ape)
	{
		return { x - ape.x, y - ape.y, z - ape.z };
	}

	vec3 operator+(vec3 ape)
	{
		return { x + ape.x, y + ape.y, z + ape.z };
	}

	vec3 operator*(float ape)
	{
		return { x * ape, y * ape, z * ape };
	}

	vec3 operator/(float ape)
	{
		return { x / ape, y / ape, z / ape };
	}

	vec3 operator/=(float ape)
	{
		x /= ape;
		y /= ape;
		z /= ape;

		return *this;
	}

	vec3 operator+=(vec3 ape)
	{
		return { x += ape.x, y += ape.y, z += ape.z };
	}

	vec3 operator-=(vec3 ape)
	{
		return { x -= ape.x, y -= ape.y, z -= ape.z };
	}

	float dot(vec3 b)
	{
		return ((this->x * b.x) + (this->y * b.y) + (this->z * b.z));
	}

	void Normalize()
	{
		while (x < 0.0f) {
			x += 360.0f;
		}
		while (x > 360.0f) {
			x = 360.0f;
		}

		while (y < 0.0f) {
			y += 360.0f;
		}
		while (y > 360.0f) {
			y = 360.0f;
		}

		z = 0.0f;
	}

	float Length()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}

	float DistTo(vec3 ape)
	{
		return (*this - ape).Length();
	}

	float Dist2D(vec3 ape)
	{
		return (*this - ape).Length2D();
	}

	float dist(vec3 b)
	{
		return sqrtf((this->x - b.x) * (this->x - b.x) + (this->y - b.y) * (this->y - b.y) + (this->z - b.z) * (this->z - b.z));
	}

	float Dot(vec3 ape)
	{
		return ((this->x * ape.x) + (this->y * ape.y) + (this->z * ape.z));
	}
};

struct vec2
{
	float x, y;

	vec2 operator-(vec2 ape)
	{
		return { x - ape.x, y - ape.y };
	}

	vec2 operator+(vec2 ape)
	{
		return { x + ape.x, y + ape.y };
	}

	vec2 operator*(float ape)
	{
		return { x * ape, y * ape };
	}

	vec2 operator/(float ape)
	{
		return { x / ape, y / ape };
	}

	vec2 operator/=(float ape)
	{
		x /= ape;
		y /= ape;

		return *this;
	}

	vec2 operator+=(vec2 ape)
	{
		return { x += ape.x, y += ape.y };
	}

	vec2 operator-=(vec2 ape)
	{
		return { x -= ape.x, y -= ape.y };
	}

	void Normalize()
	{
		while (x < 0.0f) {
			x += 360.0f;
		}
		while (x > 360.0f) {
			x = 360.0f;
		}

		while (y < 0.0f) {
			y += 360.0f;
		}
		while (y > 360.0f) {
			y = 360.0f;
		}
	}

	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}

	float Dist2D(vec2 ape)
	{
		return (*this - ape).Length2D();
	}
};


struct frameData
{
	vec2 root;
	vec2 head;
	vec2 neck;
	float distance;
};

struct frame
{
	std::vector<frameData> data;
};
