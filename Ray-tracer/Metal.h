#ifndef METAL_H
#define METAL_H

#include "Material.h"

Vec3 reflect(const Vec3& v, const Vec3& n);

class Metal : public Material {
public:
	Metal(const Vec3& a, float f);
	virtual bool scatter(const Ray& rIn, const hitRecord& rec, Vec3& attenuation, Ray& scattered) const;

private:
	Vec3 albedo;
	float fuzziness;
};

#endif