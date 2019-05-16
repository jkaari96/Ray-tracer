#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

Vec3 randomInUnitDisk();

class Camera {
public:
	Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 vup, float vfov, float aspect, float aperture, float focusDist);
	Ray getRay(float s, float t);
private:
	Vec3 origin;
	Vec3 lowerLeftCorner;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 u, v, w;
	float lensRadius;
};

#endif