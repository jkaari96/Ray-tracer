#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include <float.h>
#include <random>
#include <ctime>

#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

#include <list>
#include <thread>

Hitable *randomScene() {
	int n = 500;
	Hitable **list = new Hitable*[n + 1];
	list[0] = new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(Vec3(0.5, 0.5, 0.5)));

	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float chooseMat = RANDOM();
			Vec3 center(a+0.9f*RANDOM(),
						0.2f,b+0.9f*RANDOM());

			if ((center-Vec3(4,0.2,0)).length() > 0.9f) {
				if (chooseMat < 0.8) {
					list[i++] = new Sphere(center, 0.2f, new Lambertian(Vec3(
						RANDOM()*RANDOM(),
						RANDOM()*RANDOM(),
						RANDOM()*RANDOM())));
				}
				else if (chooseMat < 0.95) {
					list[i++] = new Sphere(center, 0.2f, new Metal(Vec3(0.5f*(1 + RANDOM()*RANDOM()),
						0.5f*(1 + RANDOM()*RANDOM()),
						0.5f*(1 + RANDOM()*RANDOM())),
						0.5f*(1 + RANDOM()*RANDOM())));
				}
				else {
					list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5f));
				}
			}
		}
	}

	list[i++] = new Sphere(Vec3(0,1,0), 1.0f, new Dielectric(1.5f));
	list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0f, new Lambertian(Vec3(0.4, 0.2, 0.1)));
	list[i++] = new Sphere(Vec3(4, 1, 0), 1.0f, new Metal(Vec3(0.7, 0.6, 0.5), 0.0));

	return new HitableList(list, i);
}

Vec3 color(const Ray& r, Hitable *world, int depth) {
	hitRecord rec;
	if (world->hit(r, 0.001f, FLT_MAX, rec)) {
		Ray scattered;
		Vec3 attenuation;
		if (depth < 50 && rec.matPtr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth+1);
		}
		else {
			return Vec3(0.0f, 0.0f, 0.0f);
		}
	}

	Vec3 unitDirection = unitVector(r.direction());
	float t = 0.5f*(unitDirection.y() + 1.0f);
	return (1.0f - t)*Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}

void renderThread(int threadIndex, int startRow, int endRow, int width, int height, int samples, Camera& cam, Hitable* world, char* data) {
	srand(time(0));

	int i = startRow * width * 3;

	for (int y = startRow; y < endRow; y++) {
		//std::clog << "Thread #" << threadIndex+1 << ": Rendering row: " << endRow - y << "/" << (endRow - startRow) << std::endl;

		for (int x = width-1; x >= 0; x--) {
			Vec3 rayColor(0.0f, 0.0f, 0.0f);

			for (int s = 0; s < samples; s++) {
				float u = float((width-x) + RANDOM()) / float(width);
				float v = float((height-y) + RANDOM()) / float(height);

				Ray r = cam.getRay(u, v);
				Vec3 p = r.pointAtParameter(2.0f);
				rayColor += color(r, world, 0);
			}

			rayColor /= float(samples);
			rayColor = Vec3(sqrtf(rayColor[0]), sqrtf(rayColor[1]), sqrtf(rayColor[2])); // Gamma correction

			int ir = int(255.99f*rayColor[0]);
			int ig = int(255.99f*rayColor[1]);
			int ib = int(255.99f*rayColor[2]);

			*(data + i) = ir;
			*(data + i + 1) = ig;
			*(data + i + 2) = ib;

			i += 3;
		}
	}
}

int main(int argc, char* argv[])
{
	srand(time(0));

	int nx = 100, ny = 100, ns = 500; // ImageWidth, ImageHeight, Samples
	char *data = nullptr;
	data = new char[nx*ny*3]; // Image data

	if (data == nullptr) {
		return EXIT_FAILURE;
	}

	Hitable* world = randomScene(); // Randomly generate a scene

	Vec3 lookFrom = Vec3(6, 1, -5);
	Vec3 lookAt = Vec3(-4, 1, 0);
	float distToFocus = (lookFrom - lookAt).length();
	float aperture = 0.1f;

	Camera cam(lookFrom, lookAt, Vec3(0, 1, 0), 32.0f, float(nx) / float(ny), aperture, distToFocus);

	const int numThreads = 2;
	std::list<std::thread> threads;

	for (int i = 0; i < numThreads; i++) {
		int startRow = i * (ny/numThreads);
		int endRow = (i + 1) * (ny / numThreads);
		threads.push_front(std::thread(renderThread, i, startRow, endRow, nx, ny, ns, std::ref(cam), world, data));
	}

	for (auto i = threads.begin(); i != threads.end(); i++) {
		i->join();
	}

	std::cout << "Finished!" << std::endl;

	stbi_write_tga("out.tga", nx, ny, 3, data);
	delete[] data;
	delete world;

	return EXIT_SUCCESS;
}
