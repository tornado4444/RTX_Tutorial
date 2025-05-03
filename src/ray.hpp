#pragma once
#include "vec3.hpp"

class ray {
public:
	ray() {}
	ray(const point3& origin, const Vec3& direction) : orig(origin), dir(direction) {}

public:
    const point3& origin() const { return orig; }
    const Vec3& direction() const { return dir; }

    point3 at(double t) const {
        return orig + t * dir;
    }
private:
    point3 orig;
    Vec3 dir;
};