#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Globals.h"
#include "Material.h"

class Dielectric : public Material {
public:
	Dielectric(float ri);
	virtual bool scatter(const Ray& rIn, const hitRecord& rec, Vec3& attenuation, Ray& scattered) const;

private:
	float refractIndex;
};


#endif