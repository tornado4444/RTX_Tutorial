#include "hittable.hpp"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittableList : public Hittable {
public:
	std::vector<shared_ptr<Hittable>> objects;

public:
	hittableList() {}
	hittableList(shared_ptr<Hittable> object) {
		add(object);
	}

public:
	void clear() {
		objects.clear();
	}

	void add(shared_ptr<Hittable> object) {
		objects.push_back(object);
	}

	bool hit(const ray& r, Interval ray_t, HitRecord& rec) const override {
		HitRecord temp_rec;
		bool hint_anything = false;
		auto closest_so_far = ray_t.max;

		for (const auto& object : objects) {
			if (object->hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
				hint_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}

		return hint_anything;
	}
};