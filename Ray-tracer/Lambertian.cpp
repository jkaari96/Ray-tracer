#include "Lambertian.h"
#include "Sphere.h"

bool Lambertian::scatter(const Ray& rIn, const hitRecord& rec, Vec3& attenuation, Ray& scattered) const {
	Vec3 target = rec.p + rec.normal + randomInUnitSphere();
	scattered = Ray(rec.p, target - rec.p);
	attenuation = albedo;
	return true;
}