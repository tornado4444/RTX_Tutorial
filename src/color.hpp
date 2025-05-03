#pragma once
#include "vec3.hpp"
#include "interval.hpp"

using color = Vec3;

inline double linear_to_gamma(double linear_component) {
	if (linear_component > 0) {
		return sqrt(linear_component);
	}
	return 0;
}

void writeColor(std::ostream& out, const color& pixelColor) {
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	// Apply a linear to gamma transform for gamma 2
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	// Translate the [0,1] component values to the byte range [0,255].
	static const Interval itensity(0.000, 0.999);
	int rbyte = static_cast<int>(256 * itensity.clamp(r));
	int gbyte = static_cast<int>(256 * itensity.clamp(g));
	int bbyte = static_cast<int>(256 * itensity.clamp(b));

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}