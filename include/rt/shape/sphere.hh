#ifndef RT_SHAPE_SPHERE_HH
#define RT_SHAPE_SPHERE_HH

#include "rt/math/ray.hh"

namespace rt {
	class intersection;

	class sphere {
	private:
		real radius;
	public:
		RT_DEVICE sphere(const real& radius);

		RT_DEVICE bool intersect(const ray3f& r, intersection& i) const;
	};
}

#endif
