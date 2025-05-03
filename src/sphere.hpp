#pragma once

#include "hittable.hpp"
#include "vec3.hpp"

#include <cmath>


class Sphere : public Hittable {
public:
	Sphere(const point3& center, double radius, shared_ptr<Material> mat)
		: center(center), radius(std::fmax(0, radius)), mat(mat) {}
	~Sphere() = default;

public:
	bool hit(const ray& r, Interval ray_t, HitRecord& rec) const override{
		Vec3 oc = center - r.origin();
		auto a = r.direction().length_squared();
		auto h = dot(r.direction(), oc);
		auto c = oc.length_squared() - pow(radius, 2);

		auto discriminant = pow(h, 2) - a * c;
		if (discriminant < 0)
			return false;

		auto sqrtd = std::sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		auto root = (h - sqrtd) / a;
		if (root <= ray_t.min || ray_t.max <= root) {
			root = (h + sqrtd) / a;
			if (root <= ray_t.min|| ray_t.max <= root)
				return false;
		}
		rec.t = root;
		rec.p = r.at(rec.t);
		Vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);
		rec.mat = mat;
		return true;
	}
private:
	point3 center;
	double radius;
	std::shared_ptr<Material> mat;
};
