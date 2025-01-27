#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

vec3 randomInUnitDisk() {
	vec3 p;
	do {
		p = 2.0 * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
	} while(dot(p, p) >= 1,0);
	return p;
}

class camera {
public:
	camera(vec3 lookFrom, vec3 lookAt, vec3 vup, float vfov, float aspect, float aperture, float focusDist) {
		lensRadius = aperture / 2;		
		float theta = vfov * M_PI / 180.0;
		float halfHeight = tan(theta / 2);
		float halfWidth = aspect * halfHeight;
		origin = lookFrom;
		w = unitVector(lookFrom - lookAt);
		u = unitVector(cross(vup, w));
		v = cross(w, u);
		lowerLeftCorner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - w * focusDist;
		horizontal = 2 * halfWidth * focusDist * u;
		vertical = 2 * halfHeight * focusDist * v;
	}

	ray getRay(float s, float t) {
		vec3 rd = lensRadius * randomInUnitDisk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - offset - origin);
	}

	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lensRadius;
};

#endif