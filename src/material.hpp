#pragma once

#include "hittable.hpp"
#include "color.hpp"

class Material {
public:
	virtual ~Material() = default;

	virtual bool scatter(
		const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered
		) const{
		return false;
	}
};

class Lambertian : public Material {
public:
	Lambertian(const color& albedo) : albedo(albedo) {}

public:
	bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override {
		auto scatter_direction = rec.normal + random_unit_vector();

		// Catch degenerate scatter direction
		if (scatter_direction.near_zero())
			scatter_direction = rec.normal;
		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}

private:
	color albedo;
};

class Metal : public Material {
public:
	Metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

public:
	bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered)
		const override {
			Vec3 reflected = reflect(r_in.direction(), rec.normal);
			reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
			scattered = ray(rec.p, reflected);
			attenuation = albedo;
			return (dot(scattered.direction(), rec.normal) > 0);
	}

private:
	color albedo;
	double fuzz;
};

class Dielectric : public Material {
public:
	Dielectric(double refraction_index) : refraction_index(refraction_index){}

	bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override {
		attenuation = color(1.0, 1.0, 1.0);
		double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;

		Vec3 unit_direction = unit_vector(r_in.direction());

		double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

		bool cannot_refract = ri * sin_theta > 1.0;
		Vec3 direction;

		if (cannot_refract || reflectance(cos_theta, ri) > random_double())
			direction = reflect(unit_direction, rec.normal);
		else
			direction = refract(unit_direction, rec.normal, ri);

		scattered = ray(rec.p, direction);
		return true;
	}
private:
	double refraction_index;

	static double reflectance(double cosine, double reflaction_index) {
		auto r0 = (1 - reflaction_index) / (1 + reflaction_index);
		r0 = pow(r0, 2);
		return r0 + (1 - r0) * std::pow((1 - cosine), 5);
	}
};