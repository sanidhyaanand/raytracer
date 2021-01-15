#ifndef SPHERE_H_
#define SPHERE_H_

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public: 
	sphere(point3 cen, double rad) : center(cen), radius(rad) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	point3 center;
	double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = 2.0f * dot(oc, r.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto dscrmt = b * b - 4.0f * a * c;
	auto sqrt_dsc = sqrt(dscrmt);

	// Check for intersection
	if (dscrmt < 0) return false;
	else { 
		// check for lower root
		auto root = (-b - sqrt_dsc) / (2.0f * a);
		if (root < t_min || root > t_max) {
			auto root = (-b + sqrt_dsc) / (2.0f * a);
			if (root < t_min) {
				return false;
			}
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		rec.normal = rec.p - center;

		return true;
	};
}

#endif