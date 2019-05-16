#include "Sphere.h"

Vec3 randomInUnitSphere() {
	Vec3 p;
	do {
		p = 2.0f*Vec3(RANDOM(), RANDOM(), RANDOM()) - Vec3(1.0f, 1.0f, 1.0f);
	} while (p.squaredLength() >= 1.0f);
	return p;
}

bool Sphere::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const {
	Vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0) {
		float temp = (-b - sqrt(b*b - a * c)) / a;

		if (temp < tMax && temp > tMin) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.matPtr = material;
			return true;
		}
		temp = (-b + sqrt(b*b - a * c)) / a;
		if (temp < tMax && temp > tMin) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.matPtr = material;
			return true;
		}
	}

	return false;
}