#ifndef HITABLELIST_H
#define HITABLELIST_H

#include "Hitable.h"

class HitableList : public Hitable {
public:
	HitableList() {}
	HitableList(Hitable** l, int n) { list = l; listSize = n; }
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const;

private:
	Hitable** list;
	int listSize;
};

#endif