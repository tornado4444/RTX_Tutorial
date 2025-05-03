#pragma once

#include "ray.hpp"
#include "interval.hpp"

class Material;

class HitRecord {
public:
	point3 p;
	Vec3 normal;
	std::shared_ptr<Material> mat;
	double t;
	bool front_face;
	
	public:
		void set_face_normal(const ray& r, const Vec3& outward_normal) {
			front_face = dot(r.direction(), outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;
		}
};

class Hittable {
public:
	virtual ~Hittable() = default;
	virtual bool hit(const ray& r, Interval ray_t, HitRecord& rec) const = 0;
};