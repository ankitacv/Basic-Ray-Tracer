#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

class material;

struct hitRecord {
	float t;
	vec3 p;
	vec3 normal;
	material* matPtr;
};

class hitable {
public:
	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};

#endif