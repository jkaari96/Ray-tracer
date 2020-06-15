#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Hitable.h"

class Triangle : public Hitable
{
public:
	Triangle() {};
	Triangle(Vec3 c, float r, Material* mat) : center(c), radius(r), material(mat) {}
	bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const;
private:
	Vec3 center;
	float radius;
	Material* material;
};

#endif TRIANGLE_H