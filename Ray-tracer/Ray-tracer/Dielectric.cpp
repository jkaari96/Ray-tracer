#include "Dielectric.h"
#include "Metal.h"

Dielectric::Dielectric(float ri) : refractIndex(ri) {

}

bool refract(const Vec3& v, const Vec3& n, float niOverNt, Vec3& refracted) {
	Vec3 uv = unitVector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0f - niOverNt * niOverNt * (1.0f - dt * dt);

	if (discriminant > 0) {
		refracted = niOverNt * (uv - n * dt) - n * sqrtf(discriminant);
		return true;
	}

	return false;
}

float schlick(float cosine, float refractIndex) {
	float r0 = (1.0f - refractIndex) / (1 + refractIndex);
	r0 *= r0;
	return r0 + (1.0f - r0)*powf((1.0f - cosine), 5.0f);
}

bool Dielectric::scatter(const Ray& rIn, const hitRecord& rec, Vec3& attenuation, Ray& scattered) const {
	Vec3 outwNormal;
	Vec3 reflected = reflect(rIn.direction(), rec.normal);
	float niOverNt;
	attenuation = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 refracted;
	float reflectProb;
	float cosine;

	if (dot(rIn.direction(), rec.normal) > 0) {
		outwNormal = -rec.normal;
		niOverNt = refractIndex;
		cosine = refractIndex * dot(rIn.direction(), rec.normal) / rIn.direction().length();
	}
	else {
		outwNormal = rec.normal;
		niOverNt = 1.0f / refractIndex;
		cosine = -dot(rIn.direction(), rec.normal) / rIn.direction().length();
	}

	if (refract(rIn.direction(), outwNormal, niOverNt, refracted)) {
		reflectProb = schlick(cosine, refractIndex);
	}
	else {
		scattered = Ray(rec.p, reflected);
		reflectProb = 1.0f;
	}

	if (RANDOM() < reflectProb) {
		scattered = Ray(rec.p, reflected);
	}
	else {
		scattered = Ray(rec.p, refracted);
	}

	return true;
}