#include "HitableList.h"

bool HitableList::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const {
	hitRecord tempRec;
	bool hitAnything = false;
	double closest = tMax;

	for (int i = 0; i < listSize; i++) {
		if (list[i]->hit(r, tMin, (float)closest, tempRec)) {
			hitAnything = true;
			closest = tempRec.t;
			rec = tempRec;
		}
	}
	return hitAnything;
}