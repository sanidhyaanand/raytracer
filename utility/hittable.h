#ifndef HITTABLE_H_
#define HITTABLE_H_

#include "ray.h"

// provides a record of our hit
struct hit_record {
    // Point of intersection
    point3 p;
    // Normal at point of intersection
    vec3 normal;
    // t value for point of intersection
    double t = 0;
};

class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif