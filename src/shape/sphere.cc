#include "rt/shape/sphere.hh"
#include "rt/math/quadratic.hh"
#include "rt/math/intersection.hh"

namespace rt {
	RT_DEVICE sphere::sphere(float_t radius) {
		this->radius = std::move(radius);
	}

	RT_DEVICE bool intersect(const sphere& s, const ray3f& r, intersection& i) {
		float_t a = 1;
		float_t b = 2 * dot(r.origin, r.direction);
		float_t c = length_squared(r.origin) - s.radius * s.radius;

		if (!quadratic_intersect(a, b, c, i.time)) {
			return false;
		}

		i.normal = normalize(r(i.time));
		i.point = i.normal * s.radius;

		return true;
	}
}
