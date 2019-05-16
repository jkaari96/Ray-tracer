#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"

class Lambertian : public Material {
public:
	Lambertian(const Vec3& a) : albedo(a) {}
	virtual bool scatter(const Ray& rIn, const hitRecord& rec, Vec3& attenuation, Ray& scattered) const;

private:
	Vec3 albedo;
};

#endif