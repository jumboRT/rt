#include "rt/shape/sphere.hh"
#include "rt/math/quadratic.hh"
#include "rt/math/intersection.hh"

namespace rt {
	RT_DEVICE sphere::sphere(const real& radius) {
		this->radius = radius;
	}

	RT_DEVICE bool sphere::intersect(const ray3f& r, intersection& i) const {
		real a = 1;
		real b = 2 * dot(r.origin, r.direction);
		real c = length_squared(r.origin) - radius * radius;

		if (!quadratic_intersect(a, b, c, i.time)) {
			return false;
		}

		i.normal = normalize(r(i.time));
		i.point = i.normal * radius;

		return true;
	}
}
