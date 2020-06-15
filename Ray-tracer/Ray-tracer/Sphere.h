#ifndef SPHERE_H
#define SPHERE_H

#include "Globals.h"
#include "Hitable.h"
#include <random>

class Sphere : public Hitable {
public:
	Sphere() {}
	Sphere(Vec3 c, float r, Material* mat) : center(c), radius(r), material(mat) {}
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const;

private:
	Vec3 center;
	float radius;
	Material* material;
};

Vec3 randomInUnitSphere();

#endif