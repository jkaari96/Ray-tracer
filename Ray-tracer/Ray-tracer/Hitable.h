#ifndef HITABLE_H
#define HITABLE_H

#include "Ray.h"

class Material;

struct hitRecord {
	float t;
	Vec3 p;
	Vec3 normal;
	Material* matPtr;
};

class Hitable {
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};

#endif