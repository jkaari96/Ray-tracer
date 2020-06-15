#include "Metal.h"
#include "Sphere.h"

Metal::Metal(const Vec3& a, float f = 0.0f) {
	if (f < 1.0f) fuzziness = f; else fuzziness = 1.0f;
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * dot(v, n)*n;
}

bool Metal::scatter(const Ray& rIn, const hitRecord& rec, Vec3& attenuation, Ray& scattered) const {
	Vec3 reflected = reflect(unitVector(rIn.direction()), rec.normal);
	scattered = Ray(rec.p, reflected + fuzziness * randomInUnitSphere());
	attenuation = albedo;
	return (dot(scattered.direction(), rec.normal)) > 0;
}
