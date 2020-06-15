#include "Camera.h"
#include "Globals.h"

Vec3 randomInUnitDisk() {
	Vec3 p;
	do {
		p = 2.0f*Vec3(RANDOM(), RANDOM(), 0.0f) - Vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0f);

	return p;
}

Camera::Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 vup, float vfov, float aspect, float aperture, float focusDist) {
	lensRadius = aperture / 2.0f;
	float theta = vfov * M_PI / 180.0f;
	float halfHeight = tanf(theta / 2.0f);
	float halfWidth = aspect * halfHeight;
	origin = lookFrom;
	w = unitVector(lookFrom - lookAt);
	u = unitVector(cross(vup, w));
	v = cross(w, u);
	lowerLeftCorner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
	horizontal = 2.0f*halfWidth*focusDist*u;
	vertical = 2.0f*halfHeight*focusDist*v;
}

Ray Camera::getRay(float s, float t) {
	Vec3 rd = lensRadius * randomInUnitDisk();
	Vec3 offset = u * rd.x() + v * rd.y();
	return Ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
}